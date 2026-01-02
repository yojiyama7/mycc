#include "mycc.h"

char *reg_1_names[] = {"dil", "sil", "dl", "cl", "r8b", "r9b"};
char *reg_4_names[] = {"edi", "esi", "edx", "ecx", "r8d", "r9d"};
char *reg_names[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};

char *filename;

void error(char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

void error_at(char *loc, char *fmt, ...) {
  va_list ap;

  char *line = loc;
  while (user_input < line && line[-1] != '\n'){
    line--;
  }

  char *end = loc;
  while (*end && *end != '\n') {
    end++;
  }
  int line_num = 1;
  for (char *p = user_input; p < line; p++) {
    if (*p == '\n') {
      line_num++;
    }
  }

  int indent = fprintf(stderr, "%s:%d: ", filename, line_num);
  fprintf(stderr, "%.*s\n", (int)(end - line), line);

  int pos = loc - line + indent;
  fprintf(stderr, "%*s", pos, "");
  fprintf(stderr, "^ ");
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, "\n");
  exit(1);
}

char *read_file(char *path) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    error("cannot open %s: %s", path, strerror(errno));
  }

  if (fseek(fp, 0, SEEK_END) == -1) {
    error("%s: fseek: %s", path, strerror(errno));
  }
  size_t size = ftell(fp);
  if (fseek(fp, 0, SEEK_SET) == -1) {
    error("%s: fseek: %s", path, strerror(errno));
  }

  char *buf = calloc(size + 2, 1);
  fread(buf, size, 1, fp);

  if (size == 0 || buf[size-1] != '\n') {
    buf[size++] = '\n';
  }
  buf[size] = '\0';
  fclose(fp);
  return buf;
}

int main(int argc, char **argv) {
	if (argc != 2) {
    fprintf(stderr, "引数の個数が正しくありません\n");
		return 1;
	}

  filename = argv[1];
  user_input = read_file(argv[1]);
  token = tokenize(user_input);
  program();
  // for (int i = 0; code[i]; i++) {
  //   print_node(code[i]);
  // }

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");

  // グローバル変数の領域確保
  printf(".data\n");
  for (GVar *gvar = globals; gvar; gvar = gvar->next) {
    printf("%.*s:\n", gvar->len, gvar->name);
    printf("  .zero %ld\n", calc_type_size(gvar->type));
  }
  // 文字列リテラル
  printf(".section .rodata\n");
  for (Node *str = string_literals; str; str = str->next) {
    printf(".LC%d:\n", str->str_id);
    printf("  .string \"%.*s\"\n", str->str_len, str->str);
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
      if (lcur->is_reg) {
        printf("  mov rax, rbp\n");
        printf("  sub rax, %d\n", lcur->offset);
        if (calc_type_size(lcur->type) == 1) {
          printf("  mov [rax], %s\n", reg_1_names[lcur->reg_idx]); // ALを使いたい
        } else if (calc_type_size(lcur->type) == 4) {
          printf("  mov [rax], %s\n", reg_4_names[lcur->reg_idx]); // EAX
        } else {
          printf("  mov [rax], %s\n", reg_names[lcur->reg_idx]);
        }
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
