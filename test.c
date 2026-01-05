int my_strlen(char *s) {
  int a;
  a = 0;
  while (*s) {
    s = s + 1;
    a = a + 1;
  }
  return a;
}

// int my_strncmp(char *a, char *b, int n) {
//   int i;
//   for (i = 0; i < n; i = i + 1) {
//     // a[i] が 0 ならここ
//     if (a[i] == 0/*'\0'*/) return a[i] - b[i];
//     // b[i] が 0 ならここ (a[i]は非zeroでb[i]と等しくない)
//     if (a[i] != b[i]) return a[i] - b[i];
//   }
//   return 0;
// }

// char *my_strstr(char *hey, char *needle) {
//   int hl; int nl; int i;
//   hl = my_strlen(hey);
//   nl = my_strlen(needle);
//   if (nl > hl) return 0/*NULL*/;
//   for (i = 0; i + nl <= hl; i = i + 1) {
//     if (my_strncmp(hey + i, needle, nl) == 0)
//       return hey + i;
//   }
//   return 0/*NULL*/;
// }

// ========

int test_variables() {
  int a; int b; a = 3; b = 5;
  test("1文字の変数", (a + 3) * b, 30);
  int foo; int bar; int baz; int xxx;
  foo = 1; bar = 2; baz = 3; xxx = 4;
  test("複数文字の変数", baz * xxx + foo * bar, 14);
}

int test_return_1() {
  return 8;
}
int test_return_2() {
  return 4;
  return 8;
}
int test_return() {
  test("return", test_return_1(), 8);
  test("複数のreturn", test_return_2(), 4);
}

int fact(int a) {
  if (a == 0)
    return 1;
  return a * fact(a - 1);
}
int fib(int a) {
  if (a == 0) return 0;
  if (a == 1) return 1;
  return fib(a-1) + fib(a-2);
}

int g_memo_fib[100];
int fib_2(int a) {
  if (a == 0) return 0;
  if (a == 1) return 1;
  if ((a < 100) * g_memo_fib[a]) return g_memo_fib[a];
  return fib_2(a-1) + fib_2(a-2);
}

int main() {
  test("整数リテラル", 0, 0);
  test("整数リテラル 2", 42, 42);
  test("足し算 1", 5+20-4, 21);
  test("足し算 2", 40 - 13 + 5, 32);
  test("掛け算", 5+6*7, 47);
  test("割り算", 10/3, 3);
  test("+x, -x", +2+(-2)+10, 10);
  test("等号", 1 == 1, 1);
  test("not equal", 10 != 42, 1);
  test("不等号 <", 5 < 3, 0);
  test("不等号 >", 5 > 3, 1);
  test("不等号 >=", 5 >= 3, 1);
  test("不等号 <=", 5 <= 3, 0);
  test("多重の丸括弧", (0 == (0 + 3)) == 0, 1);
  test_variables();
  test_return();
  int a;
  a = 1;
  if (a == 1)
    a = 2;
  test("if文(trueの時)", a, 2);
  a = 1;
  if (a == 10)
    a = 2;
  test("if文(falseの時)", a, 1);
  a = 1;
  if (a == 1)
    a = 2;
  else
    a = 3;
  test("if-else文(trueの時)", a, 2);
  a = 1;
  if (a == 10)
    a = 2;
  else
    a = 3;
  test("if-else文(falseの時)", a, 3);
  a = 1;
  int b;
  b = 0;
  while (a < 10){
    b = b + a;
    a = a + 1;
  }
  test("while文", b, 45);
  b = 1;
  for (a = 1; a < 5; a = a + 1) {
    b = b * a;
  }
  test("for文", b, 24);
  {
    a = 1; b = 1;
    a = a + b;
  }
  test("block文", a, 2);
  test("関数呼び出し", foo(), 42);
  test("関数呼び出し(副作用あり)", bar(), 0);
  test("関数呼び出し(引数1つ)", mod4(7), 3);
  test("関数呼び出し(引数6つ)", potato(1, 2, 3, 4, 5, 6), 321);
  test("再帰関数(factorial)", fact(5), 120);
  test("fib(メモ化なし)", fib(13), 233);
  int *p;
  a = 10;
  p = &a;
  test("アドレス演算子 & デリファレンス演算子", *p, 10);
  int **pp;
  a = 42;
  p = &a;
  pp = &p;
  test("2重デリファレンス", **pp, 42);
  p = alloc5(2, 4, 8, 16, 32);
  test("アドレス + 整数", *p, 2);
  test("...", *(p + 1), 4);
  test("...", *(p + 2), 8);
  test("...", *(p + 3), 16);
  test("...", *(p + 4), 32);
  p = alloc5(2, 4, 8, 16, 32);
  p = p + 5;
  test("アドレス + 整数", *(p - 1), 32);
  test("...", *(p - 2), 16);
  test("...", *(p - 3), 8);
  test("...", *(p - 4), 4);
  test("...", *(p - 5), 2);
  test("sizeof int", sizeof(42), 4);
  test("sizeof ptr", sizeof(p+100), 8);
  // "sizeof(int)"
  // "sizeof(int *)"
  int arr_int[10];
  int **arr_ptr_ptr_int[10];
  test("配列の定義", 1, 1);
  int arr[10];
  for (a = 0; a < 10; a = a + 1) {
    *(arr + a) = a * a;
    putnum(*(arr + a));
  }
  test("配列にポインタ演算でアクセス", *(arr + 3), 9);
  for (a = 0; a < 10; a = a + 1) {
    arr[a] = (10-a) * (10-a);
  }
  test("配列に添字演算でアクセス", arr[6], 16); // テストそれぞれが独立していなくていやな感じ
  test("グローバル変数を利用した再帰関数のメモ化", fib(32), 2178309);
  char c;
  test("char型変数の定義", 1, 1);
  char chars[3];
  chars[0] = -1; b = 4;
  test("char型の演算", chars[0] + b, 3);
  test("文字列リテラル", "hello"[1], 101);
  // コメント
  /*
  multi
  line
  comments
  */
  test("コメント", 1, 1);
  end_test();
}
