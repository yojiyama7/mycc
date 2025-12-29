#include "mycc.h"

char *param_regs[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
int stmt_id;

// アドレスをスタックにpushする(そのアドレスが示す先に代入などがされる)
void gen_lval(Node *node) {
  if (node->kind == NK_DEREF) {
    gen(node->lhs);
    return;
  }
  if (node->kind == NK_LVAR) {
    printf("  mov rax, rbp\n");
    printf("  sub rax, %d\n", node->offset);
    printf("  push rax\n");
    return;
  }
  error("代入の左辺値が変数ではありません");
}

void gen(Node *node) {
  int sid;
  Node *cur;

  switch (node->kind) {
  case NK_NUM:
    printf("  push %d\n", node->val);
    return;
  // LVAR単体を右辺値として処理する
  case NK_LVAR:
    gen_lval(node);
    printf("  pop rax\n");
    printf("  mov rax, [rax]\n");
    printf("  push rax\n");
    return;
  case NK_ASSIGN:
    gen_lval(node->lhs);
    gen(node->rhs);

    printf("  pop rdi\n");
    printf("  pop rax\n");
    printf("  mov [rax], rdi\n");
    printf("  push rdi\n"); // 代入式は右辺値と同じ値として評価される
    return;
  case NK_ADDR:
    gen_lval(node->lhs);
    return;
  case NK_DEREF:
    gen(node->lhs);
    printf("  pop rax\n");
    printf("  mov rax, [rax]\n");
    printf("  push rax\n");
    return;
  case NK_EXPRSTMT:
    gen(node->body);
    printf("  pop rax\n");
    return ;
  case NK_RETURN:
    printf("# >>> NK_RETURN\n");
    gen(node->lhs);
    printf("  pop rax\n");
    printf("  mov rsp, rbp\n");
    printf("  pop rbp\n");
    printf("  ret # <<< NK_RETURN\n");
    return ;
  case NK_VARDEF:
    return;
  case NK_IF:
    sid = stmt_id++;
    printf("# <<< NK_IF%d\n", sid);
    gen(node->cond);
    printf("  pop rax\n");
    printf("  cmp rax, 0\n");
    printf("  je .Lend%d\n", sid);
    gen(node->then);
    printf(".Lend%d: # <<< NK_IF%d\n", sid, sid);
    return ;
  case NK_IFELSE:
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
  case NK_WHILE:
    sid = stmt_id++;
    printf(".Lbegin%d:\n", sid);
    gen(node->cond);
    printf("  pop rax\n");
    printf("  cmp rax, 0\n");
    printf("  je  .Lend%d\n", sid);
    gen(node->body);
    printf("  jmp .Lbegin%d\n", sid);
    printf(".Lend%d:\n", sid);
    return;
  case NK_FOR:
    sid = stmt_id++;
    gen(node->init);
    printf(".Lbegin%d:\n", sid);
    gen(node->cond);
    printf("  pop rax\n");
    printf("  cmp rax, 0\n");
    printf("  je  .Lend%d\n", sid);
    gen(node->body);
    gen(node->inc);
    printf("  jmp .Lbegin%d\n", sid);
    printf(".Lend%d:\n", sid);
    return ;
  case NK_BLOCK:
    cur = node->body;
    while (cur) {
      gen(cur);
      cur = cur->next;
    }
    return ;
  case NK_CALL:
    int i = 0;
    cur = node->args;
    while (cur && i < 6) {
      gen(cur);
      printf("  pop %s\n", param_regs[i]);
      cur = cur->next;
      i++;
    }
    // 長さ6超過
    if (cur) {
      error("引数が6つ超過あります");
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
  case NK_ADD:
    printf("  add rax, rdi\n");
    break;
  case NK_SUB:
    printf("  sub rax, rdi\n");
    break;
  case NK_MUL:
    printf("  imul rax, rdi\n");
    break;
  case NK_DIV:
    printf("  cqo\n");
    printf("  idiv rdi\n");
    break;
  case NK_EQ:
    printf("  cmp rax, rdi\n");
    printf("  sete al\n");
    printf("  movzx rax, al\n");
    break;
  case NK_NE:
    printf("  cmp rax, rdi\n");
    printf("  setne al\n");
    printf("  movzx rax, al\n");
    break;
  case NK_LT:
    printf("  cmp rax, rdi\n");
    printf("  setl al\n");
    printf("  movzx rax, al\n");
    break;
  case NK_LE:
    printf("  cmp rax, rdi\n");
    printf("  setle al\n");
    printf("  movzx rax, al\n");
    break;
  default:
    break;
  }

  printf("  push rax\n");
}
