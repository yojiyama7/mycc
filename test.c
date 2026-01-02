int main() {
  printf("aaa %s %d\n", "hi", 1 + 1);
  end_test();
}

// assert_expr 15 '5*(9-6)'
// assert_expr 4 '(3+5)/2'
// assert_expr 6 '-2+(-2)+10'
// assert_expr 1 '1 == 1'
// assert_expr 1 '10 != 42'
// assert_expr 0 "5 < 3"
// assert_expr 1 "5 > 3"
// assert_expr 1 "5 >= 3"
// assert_expr 0 "5 <= 3"
// assert_expr 1 "(0 == (0 + 3)) == 0"
// # assert_expr 3 "a = 3"
// assert_stmts 30 "int a; int b; a = 3; b = 5; return (a + 3) * b;"
// assert_stmts 42 "\
// int foo; int z;
// foo = 1;
// z = 1;
// return z - foo + 42;"
// assert_stmts 14 "int foo; int bar; int baz; int xxx;\
// foo = 1; bar = 2; baz = 3; xxx = 4; return baz * xxx + foo * bar;"
// assert_stmts 8 "return 8;"
// assert_stmts 8 "return 8;\
// return 4;"
// assert_stmts 4 "\
// if ( 1 == 1 )
//   return 4;
// return 3;"
// assert_stmts 3 "\
// if ( 1 == 0 )
//   return 4;
// return 3;"
// assert_stmts 5 "\
// if ( 1 == 0 )
//   return 1;
// if ( 1 == 0 )
//   return 2;
// if ( 1 == 0 )
//   return 3;
// if ( 1 == 0 )
//   return 4;
// return 5;"
// assert_stmts 5 "\
// if (1 == 0)
//   return 3;
// else
//   return 5;"
// assert_stmts 3 "\
// if (1 != 0)
//   return 3;
// else
//   return 5;"
// assert_stmts 55 "\
// int a; int b;
// a = 0;
// b = 0;
// while (a < 10)
//   b = b + (a = a + 1);
// return b;"
// assert_stmts 6 "\
// int i;
// for (i = 0; i < 10; i = i + 1)
//   if (i * i > 30)
//     return i;
// return 42;"
// assert_stmts 42 "{ return 42; }"
// assert_stmts 32 "\
// {
//   int a; int b;
//   a = 4;
//   b = a + 4;
//   return a * b;
// }"
// assert_expr_with_asset 42 "foo()"
// assert_expr_with_asset 0 "bar()"
// assert_expr_with_asset 3 "mod4(7)"
// assert_expr_with_asset 0 "potato(1, 2, 3, 4, 5, 6) - 321"
// assert 42 "\
// int main() {
//   return 42;
// }"
// assert 23 "\
// int main() {
//   return foo(23);
// }
// int foo(int a) {
//   return a;
// }"
// assert 120 "\
// int main() {
//   return fact(5);
// }
// int fact(int a) {
//   if (a == 0)
//     return 1;
//   return a * fact(a - 1);
// }"
// assert 233 "\
// int main() {
//   return fib(13);
// }
// int fib(int a) {
//   if (a == 0)
//     return 0;
//   if (a == 1)
//     return 1;
//   return fib(a-1) + fib(a-2);
// }"
// assert_with_asset 10 "\
// int main() {
//   int a; int *b;
//   a = 10;
//   b = &a;
//   putnum(b);
//   return *b;
// }"
// assert 42 "\
// int main() {
//   int a; int *b; int **c;
//   a = 10;
//   b = &a;
//   c = &b;
//   **c = 42;
//   return a;
// }"
// assert_with_asset 4 "\
// int main() {
//   int *a;
//   a = alloc5(2, 4, 8, 16, 32);
//   putnum(*a);
//   putnum(*(a + 1));
//   putnum(*(a + 2));
//   putnum(*(a + 3));
//   putnum(*(a + 4));
//   return *(a + 1);
// }"
// assert_with_asset 32 "\
// int main() {
//   int *a;
//   a = alloc5(2, 4, 8, 16, 32);
//   a = a + 5;
//   putnum(*(a - 1));
//   putnum(*(a - 2));
//   putnum(*(a - 3));
//   putnum(*(a - 4));
//   putnum(*(a - 5));
//   return *(a - 1);
// }"
// assert_expr 4 "sizeof(42)"
// assert_stmts 8 "int *a; return sizeof(a);"
// # assert_expr 4 "sizeof(int)"
// # assert_expr 8 "sizeof(int *)"
// assert_stmts 0 "int a[10]; int **b[10];"
// assert_with_asset 9 "\
// int main() {
//   int a[10];
  
//   int i;
//   for (i = 0; i < 10; i = i + 1) {
//     *(a + i) = i * i;
//     putnum(*(a + i));
//   }
//   return *(a + 3);
// }"
// assert_with_asset 81 "\
// int main() {
//   int a[10];

//   int i;
//   for (i = 0; i < 10; i = i + 1) {
//     a[i] = i * i;
//     putnum(i[a]);
//   }
//   return a[9];
// }"
// assert 0 "\
// int g_memo[100];
// int main() {
//   return 0;
// }"
// assert 10 "\
// int a;
// int f() {
//   int a;
//   a = 10;
//   return a;
// }
// int main() {
//   a = 42;
//   return f();
// }"
// assert 42 "\
// int g_memo[100];
// int main() {
//   g_memo[99] = 42;
//   return g_memo[99];
// }"
// # これができるの非常にプログラミング言語っぽい
// assert 1 "\
// int g_memo_fib[100];
// int fib(int x) {
//   if (x == 0) return 0;
//   if (x == 1) return 1;
//   if (g_memo_fib[x] != 0) return g_memo_fib[x];
//   return fib(x-1) + fib(x-2);
// }
// int main() {
//   return fib(32) == 2178309;
// }"
// assert_stmts 0 "char a;"
// assert_stmts 3 "char a[3]; a[0] = -1; int b; b = 4; return a[0] + b;"
// assert_expr 101 '"hello"[1]'
// assert 0 "\
// int main(/* void */) {
//   int a; // variable a
// // comment
//   /*
//   multi
//   line
//   comments
//   */
// }"
// echo OK
