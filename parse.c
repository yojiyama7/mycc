#include "mycc.h"

Token *token;
char *user_input;
Node *cur_funcdef;
GVar *globals;
Node *code[100];

bool equal_str(Token *tok, char *s) {
  return (tok->len == (int)strlen(s) && memcmp(tok->str, s, tok->len) == 0);
}
// bool equal_token(Token *tok, Token *t) {
//   return (tok->len == t->len && memcpy(tok->str, t->str, tok->len) == 0);
// }

bool consume(char *op) {
  if (token->kind != TK_RESERVED || !equal_str(token, op)) {
    return false;
  }
  token = token->next;
  return true;
}

Token *consume_keyword(TokenKind tk) {
  if (token->kind != tk) {
    return NULL;
  }
  Token *tok = token;
  token = token->next;
  return tok;
}

Token *consume_type() {
  if (token->kind != TK_INT) {
    return NULL;
  }
  Token *tok = token;
  token = token->next;
  return tok;
}

Token *consume_ident(void) {
  if (token->kind != TK_IDENT) {
    return false;
  }
  Token *tok = token;
  token = token->next;
  return tok;
}

void expect(char *op) {
  if (!consume(op)) {
    error_at(token->str, "'%s'ではありません", op);
  }  
}

Token *expect_ident() {
  Token *tok = consume_ident();
  if (!tok) {
    error_at(token->str, "識別子ではありません");
  }
  return tok;
}

int expect_number(void) {
  if (token->kind != TK_NUM) {
    error_at(token->str, "数ではありません");
  }
  int val = token->val;
  token = token->next;
  return val;
}

bool at_eof(void) {
  return token->kind == TK_EOF;
}

Token *new_token(TokenKind kind, Token *cur, char *str) {
  Token *tok = calloc(1, sizeof(Token));
  tok->kind = kind;
  tok->str = str;
  cur->next = tok;
  return tok;
}

Token *tokenize(char *p) {
  Token head;
  head.next = NULL;
  Token *cur = &head;

  while (*p) {
    if (isspace(*p)) {
      p++;
      continue;
    }
    if (memcmp(p, "==", 2) == 0 ||
        memcmp(p, "!=", 2) == 0 ||
        memcmp(p, "<=", 2) == 0 ||
        memcmp(p, ">=", 2) == 0 ) {
      cur = new_token(TK_RESERVED, cur, p);
      cur->len = 2;
      p += 2;
      continue;
    }
    if (strchr("+-*/()<>=;{},&[]", *p)) {
      cur = new_token(TK_RESERVED, cur, p);
      cur->len = 1;
      p++;
      continue;
    }
    if (isalpha(*p) || *p == '_') {
      // IDENT or KEYWORD
      cur = new_token(TK_IDENT, cur, p);
      while (isalnum(*p) || *p == '_') {
        p++;
      }
      cur->len = p - cur->str;
      // KEYWORD なら kind を上書き
      if (equal_str(cur, "return")) {
        cur->kind = TK_RETURN;
      } else if (equal_str(cur, "if")) {
        cur->kind = TK_IF;
      } else if (equal_str(cur, "else")) {
        cur->kind = TK_ELSE;
      } else if (equal_str(cur, "for")) {
        cur->kind = TK_FOR;
      } else if (equal_str(cur, "while")) {
        cur->kind = TK_WHILE;
      } else if (equal_str(cur, "int")) {
        cur->kind = TK_INT;
      } else if (equal_str(cur, "sizeof")) {
        cur->kind = TK_SIZEOF;
      }
      continue;
    }
    if (isdigit(*p)) {
      cur = new_token(TK_NUM, cur, p);
      cur->val = strtol(p, &p, 10);
      continue;
    }

    error_at(p, "トークナイズできません");
  }
  new_token(TK_EOF, cur, p);
  // for (Token* t = head.next; t->kind != TK_EOF; t = t->next) {
  //   fprintf(stderr, "%s\n", t->str);
  // }
  return head.next;
}

Node *new_node(NodeKind kind, Node *lhs, Node *rhs) {
  Node *node = calloc(1, sizeof(Node));
  node->kind = kind;
  node->lhs = lhs;
  node->rhs = rhs;
  return node;
}

Node *new_num(int val) {
  Node *node = calloc(1, sizeof(Node));
  node->kind = ND_NUM;
  node->val = val;
  return node;
}

Node *new_add(Node *a, Node *b) {
  solve_type(a);
  solve_type(b);

  if (a->type->core == INT && b->type->core == INT) {
    return new_node(ND_ADD, a, b);
  }
  if (a->type->ptr_to && b->type->ptr_to) {
    error("ポインターとポインターを足すことはできません");
  }
  if (a->type->core == INT && b->type->ptr_to) {
    Node *tmp = a;
    a = b;
    b = tmp;
  }
  int size = calc_type_size(a->type->ptr_to);
  return new_node(ND_ADD, a, new_node(ND_MUL, b, new_num(size)));
}

Node *new_sub(Node *a, Node *b) {
  solve_type(a);
  solve_type(b);

  if (a->type->core == INT && b->type->core == INT) {
    return new_node(ND_SUB, a, b);
  }
  if (a->type->core == INT && b->type->ptr_to) {
    error("整数からポインターを引くことはできません");
  }
  if (a->type->ptr_to && b->type->ptr_to) {
    return new_node(ND_SUB, a, b);
  }
  int size = calc_type_size(a->type->ptr_to);
  return new_node(ND_SUB, a, new_node(ND_MUL, b, new_num(size)));
}

LVar *find_lvar(Token *tok) {
  for (LVar *var = cur_funcdef->locals; var; var = var->next) {
    if (tok->len == var->len && memcmp(tok->str, var->name, var->len) == 0) {
      return var;
    }
  }
  return NULL;
}

GVar *find_gvar(Token *tok) {
  for (GVar *var = globals; var; var = var->next) {
    if (tok->len == var->len && memcmp(tok->str, var->name, var->len) == 0) {
      return var;
    }
  }
  return NULL;
}

Node *primary(void) {
  if (consume("(")) {
    Node *node = expr();
    expect(")");
    return node;
  }
  Token *tok = consume_ident();
  if (tok) {
    LVar *lvar = find_lvar(tok);
    // LVAR
    if (lvar) {
      Node *node = calloc(1, sizeof(Node));
      node->kind = ND_LVAR;
      node->offset = lvar->offset;
      node->type = lvar->type;
      return node;
    }
    GVar *gvar = find_gvar(tok);
    if (gvar) {
      Node *node = calloc(1, sizeof(Node));
      node->kind = ND_GVAR;
      node->gvar_name = gvar->name;
      node->gvar_name_len = gvar->len;
      node->type = gvar->type;
      return node;
    }
    Node *node = calloc(1, sizeof(Node));
    node->kind = ND_FUNCNAME;
    node->func_name = tok->str;
    node->func_name_len = tok->len;
    return node;
  }

  return new_num(expect_number());
}

Node *postfix(void) {
  Node *node = primary();

  while (true) {
    if (consume("(")) {
      // CALL
      Node *nd = calloc(1, sizeof(Node));
      nd->kind = ND_CALL;
      if (node->kind == ND_LVAR) { // QUESTION: これっている？ // 型で見た方がいいかも
        error("ローカル変数を呼び出ししています");
      }
      nd->func_name = node->func_name;
      nd->func_name_len = node->func_name_len;
      Node head; head.next = NULL;
      Node *cur = &head;
      if (!consume(")")) {
        // 引数がある時
        cur->next = expr();
        cur = cur->next;
        // 2つ以上引数がある時
        while (!consume(")")) {
          expect(",");
          cur->next = expr();
          cur = cur->next;
        }
      }
      nd->args = head.next;
      node = nd;
      continue;
    }
    if (consume("[")) {
      node = new_node(ND_DEREF, new_add(node, expr()), NULL);
      expect("]");
      continue;
    }

    return node;
  }
}

Node *unary(void) {
	if (consume("+")) {
		return postfix();
	}
	if (consume("-")) {
		return new_node(ND_SUB, new_num(0), postfix());
	}
  if (consume("*")) {
    return new_node(ND_DEREF, unary(), NULL);
  }
  if (consume("&")) {
    return new_node(ND_ADDR, unary(), NULL);
  }
  if (consume_keyword(TK_SIZEOF)) {
    Node *u = unary();
    solve_type(u);
    return new_num(calc_type_size(u->type));
  }
	return postfix();
}

Node *mul(void) {
  Node *node = unary();
  while (true) {
    if (consume("*")) {
      node = new_node(ND_MUL, node, unary());
    } else if (consume("/")) {
      node = new_node(ND_DIV, node, unary());
    } else {
      return node;
    }
  }
}

Node *add(void) {
  Node *node = mul();
  while (true) {
    if (consume("+")) {
      node = new_add(node, mul());
    } else if (consume("-")) {
      node = new_sub(node, mul());
    } else {
      return node;
    }
  }
}

Node *relational(void) {
  Node *node = add();
  if (consume("<=")) {
    return new_node(ND_LE, node, add());
  }
  if (consume(">=")) {
    return new_node(ND_LE, add(), node);
  }
  if (consume("<")) {
		return new_node(ND_LT, node, add());
	}
	if (consume(">")) {
    return new_node(ND_LT, add(), node);
  }
  return node;
}

Node *equality(void) {
  Node *node = relational();
  if (consume("==")) {
    return new_node(ND_EQ, node, add());
  }
  if (consume("!=")) {
    return new_node(ND_NE, node, add());
  }
  return node;
}

Node *assign(void) {
  Node *node = equality();

  if (consume("=")) {
    return new_node(ND_ASSIGN, node, assign());
  }

  return node;
}

Node *expr(void) {
  return assign();
}

Type *try_decl(Token **ident_token) {
  Token *tok = consume_type();
  if (!tok) {
    return NULL;
  }
  Type *type;
  if (tok->kind == TK_INT) {
    type = ty_int;
  }
  while (consume("*")) {
    type = pointer_to(type);
  }
  *ident_token = expect_ident();
  while (consume("[")) {
    type = array_of(type);
    type->array_size = expect_number();
    expect("]");
  }
  return type;
}

Node *stmt(void) {
  Node *node;
  // IF, IFELSE
  if (consume_keyword(TK_IF)) {
    node = calloc(1, sizeof(Node));
    node->kind = ND_IF;
    expect("(");
    node->cond = expr();
    expect(")");
    node->then = stmt();
    // IFELSE
    if (consume_keyword(TK_ELSE)) {
      node->kind = ND_IFELSE;
      node->els = stmt();
    }
    return node;
  }
  if (consume_keyword(TK_WHILE)) {
    node = calloc(1, sizeof(Node));
    node->kind = ND_WHILE;
    expect("(");
    node->cond = expr();
    expect(")");
    node->then = stmt();
    return node;
  }
  if (consume_keyword(TK_FOR)) {
    node = calloc(1, sizeof(Node));
    node->kind = ND_FOR;
    expect("(");
    if (!consume(";")) {
      node->init = expr();
      expect(";");
    }
    if (!consume(";")) {
      node->cond = expr();
      expect(";");
    }
    node->inc = expr();
    expect(")");
    node->then = stmt();
    return node;
  }
  if (consume("{")) {
    node = calloc(1, sizeof(Node));
    node->kind = ND_BLOCK;
    Node head; head.next = NULL;
    Node *cur = &head;
    while (!consume("}")) {
      cur->next = stmt();
      cur = cur->next;
    }
    node->body = head.next;
    return node;
  }

  // 変数定義
  Token *ident;
  Type *type = try_decl(&ident);
  if (type) {
    node = calloc(1, sizeof(Node));
    node->kind = ND_VARDEF;
    if (find_lvar(ident)) {
      error("既に定義された変数名です");
    }
    LVar *lvar = calloc(1, sizeof(LVar));
    lvar->next = cur_funcdef->locals;
    lvar->type = type;
    lvar->name = ident->str;
    lvar->len = ident->len;
    node->defined_var = lvar;
    if (cur_funcdef->locals == NULL) { // XXX: localsがNULLになっているかもしれないのいやだね
      lvar->offset = calc_type_mem_size(type);
    } else {
      lvar->offset = cur_funcdef->locals->offset + calc_type_mem_size(type);
    }
    cur_funcdef->locals = lvar;
  } else if (consume_keyword(TK_RETURN)) {
    // RETURN
    node = calloc(1, sizeof(Node));
    node->kind = ND_RETURN;
    node->lhs = expr();
  } else {
    node = calloc(1, sizeof(Node));
    node->kind = ND_EXPRSTMT;
    node->lhs = expr();
  }
  expect(";");
  return node;
}

// 再起的に呼ばれることはないと仮定
Node *toplevel(void) {
  Token *ident;
  Type *type = try_decl(&ident);
  if (!type) {
    error("関数定義・グローバル変数定義のための型がありません");
  }
  Node *node = calloc(1, sizeof(Node));
  if (consume("(")) {
    // FUNC_DEF
    node->kind = ND_FUNCDEF;
    node->type = type;
    node->func_name = ident->str;
    node->func_name_len = ident->len;
    cur_funcdef = node; // 再起的に呼ばれないので問題ない
    Node head; head.next = NULL;
    Node *cur = &head;
    int i = 0;
    while (!consume(")") && i < 6) {
      Token *ident;
      type = try_decl(&ident);
      if (!type) {
        error("引数宣言のための型がありません");
      }
      LVar *lvar = find_lvar(ident);
      if (lvar) {
        error_at(ident->str, "同名の引数があります");
      }
      lvar = calloc(1, sizeof(LVar));
      lvar->next = cur_funcdef->locals;
      lvar->type = type;
      lvar->name = ident->str;
      lvar->len = ident->len;
      lvar->reg = param_regs[i];
      if (cur_funcdef->locals == NULL) { // XXX: localsがNULLになっているかもしれないのいやだね
        lvar->offset = calc_type_mem_size(type);
      } else {
        lvar->offset = cur_funcdef->locals->offset +  calc_type_mem_size(type);
      }
      node->offset = lvar->offset;
      cur_funcdef->locals = lvar;
      if (!consume(",")) {
        expect(")");
        break;
      }
      cur = cur->next;
      i++;
    }
    if (i == 6) {
      error_at(token->str, "引数が6つ超過あります");
    }
    node->body = stmt();
    return node;
  }
  // GVAR;
  node->kind = ND_GVARDEF;
  if (find_gvar(ident)) {
    error("すでに同名のグローバル変数があります");
  }
  while (consume("[")) {
    type = array_of(type);
    type->array_size = expect_number();
    expect("]");
  }
  expect(";");
  GVar *gvar = calloc(1, sizeof(GVar));
  gvar->type = type;
  gvar->name = ident->str;
  gvar->len = ident->len;
  gvar->next = globals;
  globals = gvar;
  node->type = type;
  node->defined_gvar = gvar;
  return node;
}

void program(void) {
  int i = 0;

  while (!at_eof()) {
    code[i++] = toplevel();
    if (i >= 100) {
      error_at(token->str, "コードが多すぎます");
    }
  }
  code[i] = NULL;
}
