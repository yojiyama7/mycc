#include "mycc.h"

Token *token;
char *user_input;
Node *cur_funcdef;
Node *code[100];

bool consume(char *op) {
  if (token->kind != TK_RESERVED ||
      (int)strlen(op) != token->len ||
      memcmp(op, token->str, token->len) != 0) {
    return false;
  }
  token = token->next;
  return true;
}

bool consume_keyword(char *op) {
  if (!(token->kind == TK_RETURN ||
      token->kind == TK_IF ||
      token->kind == TK_ELSE ||
      token->kind == TK_FOR ||
      token->kind == TK_WHILE) ||
      (int)strlen(op) != token->len ||
      memcmp(op, token->str, token->len) != 0) {
    return false;
  }
  token = token->next;
  return true;
}

Token *consume_ident(void) {
  if (token->kind != TK_IDENT) {
    return NULL;
  }
  Token *tok = token;
  token = token->next;
  return tok;
}

void expect(char *op) {
  if (token->kind != TK_RESERVED ||
      (int)strlen(op) != token->len ||
      memcmp(op, token->str, token->len) != 0) {
    error_at(token->str, "'%s'ではありません", op);
  }
  token = token->next;
}

Token *expect_ident() {
  if (token->kind != TK_IDENT) {
    error_at(token->str, "識別子ではありません");
  }
  Token *ident = token;
  token = token->next;
  return ident;
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
    if (*p == '+' ||
        *p == '-' ||
        *p == '*' ||
        *p == '/' ||
        *p == '(' ||
        *p == ')' ||
        *p == '<' ||
        *p == '>' ||
        *p == '=' ||
        *p == ';' ||
        *p == '{' ||
        *p == '}' ||
        *p == ',' ||
        *p == '&' ) {
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
      if (cur->len == 6 && memcmp(cur->str, "return", 6) == 0) {
        cur->kind = TK_RETURN;
      } else if (cur->len == 2 && memcmp(cur->str, "if", 2) == 0) {
        cur->kind = TK_IF;
      } else if (cur->len == 4 && memcmp(cur->str, "else", 4) == 0) {
        cur->kind = TK_ELSE;
      } else if (cur->len == 3 && memcmp(cur->str, "for", 3) == 0) {
        cur->kind = TK_FOR;
      } else if (cur->len == 5 && memcmp(cur->str, "while", 5) == 0) {
        cur->kind = TK_WHILE;
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

Node *new_node_num(int val) {
  Node *node = calloc(1, sizeof(Node));
  node->kind = NK_NUM;
  node->val = val;
  return node;
}

LVar *find_lvar(Token *tok) {
  for (LVar *var = cur_funcdef->locals; var; var = var->next) {
    if (var->len == tok->len && memcmp(tok->str, var->name, var->len) == 0) {
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
    if (consume("(")) {
      Node *node = calloc(1, sizeof(Node));
      node->kind = NK_CALL;
      if (find_lvar(tok)) { // QUESTION: これっている？
        error("ローカル変数を呼び出ししています");
      }
      node->func_name = tok->str;
      node->func_name_len = tok->len;
      Node head;
      head.next = NULL;
      Node *cur = &head;
      while (!consume(")")) {
        cur->next = expr();
        if (!consume(",")) {
          expect(")");
          break;
        }
        cur = cur->next;
      }
      node->args = head.next;
      return node;
    }
    Node *node = calloc(1, sizeof(Node));
    node->kind = NK_LVAR;

    LVar *lvar = find_lvar(tok);
    if (lvar) {
      node->offset = lvar->offset;
    } else {
      lvar = calloc(1, sizeof(LVar));
      lvar->next = cur_funcdef->locals;
      lvar->name = tok->str;
      lvar->len = tok->len;
      if (cur_funcdef->locals == NULL) { // XXX: localsがNULLになっているかもしれないのいやだね
        lvar->offset = 8;
      } else {
        lvar->offset = cur_funcdef->locals->offset + 8;
      }
      node->offset = lvar->offset;
      cur_funcdef->locals = lvar;
    }
    return node;
  }

  return new_node_num(expect_number());
}

Node *unary(void) {
	if (consume("+")) {
		return primary();
	}
	if (consume("-")) {
		return new_node(NK_SUB, new_node_num(0), primary());
	}
  if (consume("*")) {
    return new_node(NK_DEREF, unary(), NULL);
  }
  if (consume("&")) {
    return new_node(NK_ADDR, unary(), NULL);
  }
	return primary();
}

Node *mul(void) {
  Node *node = unary();

  while (true) {
    if (consume("*")) {
      node = new_node(NK_MUL, node, unary());
    } else if (consume("/")) {
      node = new_node(NK_DIV, node, unary());
    } else {
      return node;
    }
  }
}

Node *add(void) {
  Node *node = mul();
  while (true) {
    if (consume("+")) {
      node = new_node(NK_ADD, node, mul());
    } else if (consume("-")) {
      node = new_node(NK_SUB, node, mul());
    } else {
      return node;
    }
  }
}

Node *relational(void) {
  Node *node = add();
  if (consume("<=")) {
    return new_node(NK_LE, node, add());
  }
  if (consume(">=")) {
    return new_node(NK_LE, add(), node);
  }
  if (consume("<")) {
		return new_node(NK_LT, node, add());
	}
	if (consume(">")) {
    return new_node(NK_LT, add(), node);
  }
  return node;
}

Node *equality(void) {
  Node *node = relational();
  if (consume("==")) {
    return new_node(NK_EQ, node, add());
  }
  if (consume("!=")) {
    return new_node(NK_NE, node, add());
  }
  return node;
}

Node *assign(void) {
  Node *node = equality();

  if (consume("=")) {
    return new_node(NK_ASSIGN, node, assign());
  }

  return node;
}

Node *expr(void) {
  return assign();
}

Node *stmt(void) {
  Node *node;
  
  // IF, IFELSE
  if (consume_keyword("if")) {
    node = calloc(1, sizeof(Node));
    node->kind = NK_IF;
    expect("(");
    node->cond = expr();
    expect(")");
    node->then = stmt();
    // IFELSE
    if (consume_keyword("else")) {
      node->kind = NK_IFELSE;
      node->els = stmt();
    }
    return node;
  }
  if (consume_keyword("while")) {
    node = calloc(1, sizeof(Node));
    node->kind = NK_WHILE;
    expect("(");
    node->cond = expr();
    expect(")");
    node->body = stmt();
    return node;
  }
  if (consume_keyword("for")) {
    node = calloc(1, sizeof(Node));
    node->kind = NK_FOR;
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
    node->body = stmt();
    return node;
  }
  if (consume("{")) {
    node = calloc(1, sizeof(Node));
    node->kind = NK_BLOCK;
    Node head;
    head.next = NULL;
    Node *cur = &head;
    while (!consume("}")) {
      cur->next = stmt();
      cur = cur->next;
    }
    node->body = head.next;
    return node;
  }

  if (consume_keyword("return")) {
    // RETURN
    node = calloc(1, sizeof(Node));
    node->kind = NK_RETURN;
    node->lhs = expr();
  } else {
    node = calloc(1, sizeof(Node));
    node->kind = NK_EXPRSTMT;
    node->body = expr();
  }
  expect(";");
  return node;
}

// 再起的に呼ばれることはないと仮定
Node *funcdef(void) {
  Token *ident = consume_ident(); // expect_ident
  if (!ident) {
    error_at(token->str, "関数名ではありません");
  }
  Node *node = calloc(1, sizeof(Node));
  node->kind = NK_FUNCDEF;
  node->func_name = ident->str;
  node->func_name_len = ident->len;
  cur_funcdef = node; // 再起的に呼ばれないので問題ない
  expect("(");
  Node head;
  head.next = NULL;
  Node *cur = &head;
  int i = 0;
  while (!consume(")") && i < 6) {
    Token *ident = expect_ident();
    LVar *lvar = find_lvar(ident);
    if (lvar) {
      error_at(ident->str, "同名の引数があります");
    } else {
      lvar = calloc(1, sizeof(LVar));
      lvar->next = cur_funcdef->locals;
      lvar->name = ident->str;
      lvar->len = ident->len;
      lvar->reg = param_regs[i];
      if (cur_funcdef->locals == NULL) { // XXX: localsがNULLになっているかもしれないのいやだね
        lvar->offset = 8;
      } else {
        lvar->offset = cur_funcdef->locals->offset + 8;
      }
      node->offset = lvar->offset;
      cur_funcdef->locals = lvar;
    }
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

void program(void) {
  int i = 0;
  
  while (!at_eof()) {
    code[i++] = funcdef();
    if (i >= 100) {
      error_at(token->str, "コードが多すぎます");
    }
  }
  code[i] = NULL;
}
