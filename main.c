#include "mycc.h"

void error(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  vfprintf(stderr, fmt, ap);
  exit(1);
}

void error_at(char *loc, char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  int pos = loc - user_input;
  fprintf(stderr, "%s\n", user_input);
  fprintf(stderr, "%*s", pos, " ");
  fprintf(stderr, "^ ");
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

int main(int argc, char **argv) {
	if (argc != 2) {
    fprintf(stderr, "引数の個数が正しくありません\n");
		return 1;
	}

  user_input = argv[1];
  token = tokenize(argv[1]);
  program();

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");

  printf(".data\n");
  // グローバル変数の領域確保
  for (GVar *gvar = globals; gvar; gvar = gvar->next) {
    printf("%.*s:\n", gvar->len, gvar->name);
    printf("  .zero %ld\n", calc_type_size(gvar->type));
  }

  printf(".text\n");
  for (int i = 0; code[i]; i++) {
    if (code[i]->kind != ND_FUNCDEF) {
      continue;
    }
    printf("%.*s:\n", code[i]->func_name_len, code[i]->func_name);

    // プロローグ
    printf("  push rbp\n"); // rpbの保持
    printf("  mov rbp, rsp\n");
    if (code[i]->locals) {
      printf("  sub rsp, %d\n", code[i]->locals->offset);
    }
    LVar *lcur = code[i]->locals;
    while (lcur) {
      printf("  # ローカル変数名: %.*s\n", lcur->len, lcur->name);
      if (lcur->reg) {
        printf("  mov rax, rbp\n");
        printf("  sub rax, %d\n", lcur->offset);
        printf("  mov [rax], %s\n", lcur->reg);
      }
      lcur = lcur->next;
    }
    printf("  # vvv\n");

    gen(code[i]->body);

    // エピローグ
    printf("  # ^^^\n");
    printf("  mov rsp, rbp\n"); // 関数フレーム(or stack)をrbpの示すアドレスまで縮小
    printf("  pop rbp\n");
    printf("  mov rax, 0\n"); // 明示がなければ0を返す
    printf("  ret\n");
  }

	return 0;
}
