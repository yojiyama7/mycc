#include "mycc.h"

int stmt_id;

// アドレスをスタックにpushする(そのアドレスが示す先に代入などがされる)
void gen_lval(Node *node) {
  if (node->kind == ND_DEREF) {
    gen(node->lhs);
    return;
  }
  if (node->kind == ND_LVAR) {
    printf("  mov rax, rbp\n");
    printf("  sub rax, %d\n", node->offset);
    printf("  push rax\n");
    return;
  }
  if (node->kind == ND_GVAR) {
    printf("  lea rax, %.*s[rip]\n", node->gvar_name_len, node->gvar_name);
    printf("  push rax\n");
    return;
  }
  // print_node(node);
  error("左辺値として有効なアドレスを取得できません");
}

void gen(Node *node) {
  int sid;
  Node *cur;

  switch (node->kind) {
  case ND_NUM:
    printf("  push %d\n", node->val);
    return;
  case ND_STRING:
    printf("  lea rax, [rip + .LC%d]\n", node->str_id);
    printf("  push rax\n");
    return;
  // LVAR単体を右辺値として処理する
  case ND_LVAR:
    gen_lval(node);
    if (node->type->core == ARRAY) {
      return;
    }
    printf("  pop rax\n");
    solve_type(node);
    if (calc_type_size(node->type) == 1) {
      printf("  movsx rax, BYTE PTR [rax]\n");
    } else if (calc_type_size(node->type) == 4) {
      printf("  mov eax, [rax]\n");
    } else {
      printf("  mov rax, [rax]\n");
    }
    printf("  push rax\n");
    return;
  case ND_GVAR:
    gen_lval(node);
    if (node->type->core == ARRAY) {
      return;
    }
    printf("  pop rax\n");
    solve_type(node);
    if (calc_type_size(node->type) == 1) {
      printf("  movsx rax, BYTE PTR [rax]\n");
    } else if (calc_type_size(node->type) == 4) {
      printf("  mov eax, [rax]\n");
    } else {
      printf("  mov rax, [rax]\n");
    }
    printf("  push rax\n");
    return;
  case ND_ASSIGN:
    gen_lval(node->lhs);
    gen(node->rhs);
    printf("  pop rdi\n");
    printf("  pop rax\n");
    solve_type(node->lhs);
    if (calc_type_size(node->lhs->type) == 1) {
      printf("  mov [rax], dil\n");
    } else if (calc_type_size(node->lhs->type) == 4) {
      printf("  mov [rax], edi\n");
    } else {
      printf("  mov [rax], rdi\n");
    }
    printf("  push rdi\n"); // 代入式は右辺値と同じ値として評価される
    return;
  case ND_ADDR:
    gen_lval(node->lhs);
    return;
  case ND_DEREF:
    gen(node->lhs);
    printf("  pop rax\n");
    solve_type(node);
    if (calc_type_size(node->type) == 1) {
      printf("  movsx rax, BYTE PTR [rax]\n");
    } else if (calc_type_size(node->type) == 4) {
      printf("  mov eax, [rax]\n");
    } else {
      printf("  mov rax, [rax]\n");
    }
    printf("  push rax\n");
    return;
  case ND_EXPRSTMT:
    gen(node->lhs);
    printf("  pop rax\n");
    return ;
  case ND_RETURN:
    printf("# >>> ND_RETURN\n");
    gen(node->lhs);
    printf("  pop rax\n");
    printf("  mov rsp, rbp\n");
    printf("  pop rbp\n");
    printf("  ret # <<< ND_RETURN\n");
    return ;
  case ND_VARDEF:
    return;
  case ND_GVARDEF:
    return;
  case ND_IF:
    sid = stmt_id++;
    printf("# <<< ND_IF%d\n", sid);
    gen(node->cond);
    printf("  pop rax\n");
    printf("  cmp rax, 0\n");
    printf("  je .Lend%d\n", sid);
    gen(node->then);
    printf(".Lend%d: # <<< ND_IF%d\n", sid, sid);
    return ;
  case ND_IFELSE:
    sid = stmt_id++;
    gen(node->cond);
    printf("  pop rax\n");
    printf("  cmp rax, 0\n");
    printf("  je .Lelse%d\n", sid);
    gen(node->then);
    printf("  jmp .Lend%d\n", sid);
    printf(".Lelse%d:\n", sid);
    gen(node->els);
    printf(".Lend%d:\n", sid);
    return ;
  case ND_WHILE:
    sid = stmt_id++;
    printf(".Lbegin%d:\n", sid);
    gen(node->cond);
    printf("  pop rax\n");
    printf("  cmp rax, 0\n");
    printf("  je  .Lend%d\n", sid);
    gen(node->then);
    printf("  jmp .Lbegin%d\n", sid);
    printf(".Lend%d:\n", sid);
    return;
  case ND_FOR:
    sid = stmt_id++;
    gen(node->init);
    printf(".Lbegin%d:\n", sid);
    gen(node->cond);
    printf("  pop rax\n");
    printf("  cmp rax, 0\n");
    printf("  je  .Lend%d\n", sid);
    gen(node->then);
    gen(node->inc);
    printf("  jmp .Lbegin%d\n", sid);
    printf(".Lend%d:\n", sid);
    return ;
  case ND_BLOCK:
    cur = node->body;
    while (cur) {
      gen(cur);
      cur = cur->next;
    }
    return ;
  case ND_CALL:
    int i = 0;
    cur = node->args;
    while (cur) {
      gen(cur);
      printf("  pop %s\n", reg_names[i]);
      cur = cur->next;
      i++;
    }
    printf("  push rbp\n");     // XXX: rbpをスタックに積んで
    printf("  mov rbp, rsp\n"); // rbpにrspを一時保存して
    printf("  and rsp, -16\n");
    printf("  call %.*s\n", node->func_name_len, node->func_name);
    printf("  mov rsp, rbp\n"); // rspを復元して
	  printf("  pop rbp\n");      // rbpを復元
    printf("  push rax\n");
    return;
  default:
    break;
  }

  gen(node->lhs);
  gen(node->rhs);

  printf("  pop rdi\n");
  printf("  pop rax\n");

  switch (node->kind) {
  case ND_ADD:
    printf("  add rax, rdi\n");
    break;
  case ND_SUB:
    printf("  sub rax, rdi\n");
    break;
  case ND_MUL:
    printf("  imul rax, rdi\n");
    break;
  case ND_DIV:
    printf("  cqo\n");
    printf("  idiv rdi\n");
    break;
  case ND_EQ:
    printf("  cmp rax, rdi\n");
    printf("  sete al\n");
    printf("  movzx rax, al\n");
    break;
  case ND_NE:
    printf("  cmp rax, rdi\n");
    printf("  setne al\n");
    printf("  movzx rax, al\n");
    break;
  case ND_LT:
    printf("  cmp rax, rdi\n");
    printf("  setl al\n");
    printf("  movzx rax, al\n");
    break;
  case ND_LE:
    printf("  cmp rax, rdi\n");
    printf("  setle al\n");
    printf("  movzx rax, al\n");
    break;
  default:
    break;
  }

  printf("  push rax\n");
}
