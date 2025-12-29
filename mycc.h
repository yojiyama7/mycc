#pragma once

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  TK_NUM,
  TK_RESERVED,
  // keyword
  TK_RETURN,
  TK_IF,
  TK_ELSE,
  TK_FOR,
  TK_WHILE,
  TK_IDENT,
  TK_INT,
  // ---
  TK_EOF,
} TokenKind;

typedef struct s_Token Token;
struct s_Token {
  TokenKind kind; // トークンの型
  Token *next;    // 次の入力トークン
  int val;        // kindがTK_NUMの場合、その数値
  char *str;      // トークン文字列の先頭ポインタ
  int len;        // トークン文字列の長さ
};

typedef enum {
  // リテラル[単項のr-value]
  ND_NUM,       // 123
  // l-value
  ND_LVAR,
  // 二項演算 (r-value, r-value) -> r-value
  ND_ADD,       // +
  ND_SUB,       // -
  ND_MUL,       // *
  ND_DIV,       // /
  ND_EQ,        // ==
  ND_NE,        // !=
  ND_LT,        // <
  ND_LE,        // <=
  // 二項演算 (l-value, r-value) -> r-value
  ND_ASSIGN,    // =
  // 単項演算子 (r-value) -> r-value
  ND_DEREF,     // *     前置
  ND_CALL,      // (...) 後置
  // 単項演算子 (l-value) -> r-value
  ND_ADDR,      // &     前置
  // ;で終わる文
  ND_EXPRSTMT,  // <#r-value#>;
  ND_RETURN,    // return <#r-value#>;
  ND_VARDEF,    // <#type#> <#decl#>;
  // 制御構文
  ND_IF,
  ND_IFELSE,
  ND_FOR,
  ND_WHILE,
  ND_BLOCK,     // {}
  // 関数定義
  ND_FUNCDEF,
} NodeKind;

typedef enum {
  TY_INT,
  TY_PTR,
} TypeKind;

typedef struct s_Type Type;
struct s_Type {
  TypeKind type;
  Type *ptr_to;
};

typedef struct s_LVar LVar;
struct s_LVar {
  LVar *next;
  Type *type;
  char *name;
  int len;
  int offset;
  char *reg; // 引数を疑似的にローカル変数にしている場合、レジスタ名を入れる
};

typedef struct s_Node Node;
struct s_Node {
  NodeKind kind;
  Node *lhs;  // 二項演算子: 左辺
              // 単項演算子: 単体の被演算子
  Node *rhs;  // 二項演算子: 右辺
  int val;    // ND_NUM: 値
  int offset; // ND_LVAR: ローカル変数のオフセット値

  Type *type; // expr系: 評価された時の型
              // FUNCDEF: 関数の返り値の型

  Node *cond; // IF | IFELSE | FOR | WHILE:
              //              条件式
  Node *then; // IF | FOR | WHILE:
              //              条件を満たした際に実行される文
  Node *els;  // IFELSE:      条件を満たさなかった際に実行される文
  Node *init; // FOR:         初期化式
  Node *inc;  // FOR:         更新式
  Node *body; // BLOCK:       中身の文たちのうち1番目
              // FUNCDEF:     関数の中身の文
  char *func_name;    // CALL, FUNCDEF // XXX: 問題ありそう Node *func; にしたいけども一旦許容 incrimental にいこう
  int func_name_len;  // CALL, FUNCDEF

  Node *args;         // CALL: 実引数(expr)たちのうち1番目
  // XXX: func が冗長だな、、、
  LVar *locals;       // FUNCDEF: ローカル変数(LVar)たちのうち 最後に定義された要素
  LVar *defined_var;  // VARDEF: 自身(VARDEF型のあるNode)が定義した変数

  Node *next; // BLOCK: body を先頭とする stmt たち
              // CALL:  args を先頭とする expr たち
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
