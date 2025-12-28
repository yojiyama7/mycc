#pragma once

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  TK_RESERVED,
  TK_RETURN,
  TK_IF,
  TK_ELSE,
  TK_FOR,
  TK_WHILE,
  TK_IDENT,
  TK_NUM,
  TK_EOF,
} TokenKind;

typedef struct s_Token Token;
struct s_Token {
  TokenKind kind; // トークンの型
  Token *next;    // 次の入力トークン
  int val;        // kindがTK_NUMの場合、その数値
  char *str;      // トークン文字列
  int len;
};

typedef enum {
  NK_ADD,
  NK_SUB,
  NK_MUL,
  NK_DIV,
  NK_EQ,
  NK_NE,
  NK_LT,
  // NK_GT,
  NK_LE,
  // NK_GE,
  NK_ASSIGN,
  NK_LVAR,
  NK_NUM,
  NK_DEREF,
  NK_ADDR,
  NK_EXPRSTMT,
  NK_RETURN,
  NK_IF,
  NK_IFELSE,
  NK_FOR,
  NK_WHILE,
  NK_BLOCK,
  NK_CALL,
  NK_FUNCDEF,
  NK_PARAM,
} NodeKind;

typedef struct s_LVar LVar;
struct s_LVar {
  LVar *next;
  char *name;
  int len;
  int offset;
  char *reg; // 引数を疑似的にローカル変数にしている場合、レジスタ名を入れる
};

typedef struct s_Node Node;
struct s_Node {
  NodeKind kind;
  Node *lhs;
  Node *rhs;
  int val;    // kindがNK_NUMの場合のみ使う
  int offset; // kindがNK_LVARの場合のみ使う

  Node *cond; // IF, IFELSE, FOR, WHILE
  Node *then; // IF, IFELSE
  Node *els;  // IFELSE
  Node *init; // FOR
  Node *inc;  // FOR
  Node *body; // FOR, WHILE, BLOCK, FUNCDEF
  char *func_name;    // CALL, FUNCDEF // XXX: 問題ありそう Node *func; にしたいけども一旦許容 incrimental にいこう
  int func_name_len;  // CALL, FUNCDEF
  Node *args;         // CALL
  char *param_name;   // PARAM
  int param_name_len; // PARAM
  // XXX: param, func が冗長だな、、、
  LVar *locals; // FUNCDEF

  Node *next; // BLOCK, CALL, PARAM
};

extern Token *token;
extern char *user_input;
extern Node *cur_funcdef;
extern Node *code[100];
extern char *param_regs[];

void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);

Token *tokenize(char *p);
Node *expr(void);
void program(void);
void gen(Node *node);
