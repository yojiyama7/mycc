#!/bin/bash

assert() {
  expected="$1"
  input="$2"
  ./mycc "$input" > tmp.s
  cc -z noexecstack -o tmp tmp.s # -z noexecstack で何らかの警告を黙らせている
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert_expr() {
  expected="$1"
  input="$2"
  ./mycc "main() { return $input; }" > tmp.s
  cc -z noexecstack -o tmp tmp.s # -z noexecstack で何らかの警告を黙らせている
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}


assert_stmts() {
  expected="$1"
  input="$2"
  ./mycc "main() { $input }" > tmp.s
  cc -z noexecstack -o tmp tmp.s # -z noexecstack で何らかの警告を黙らせている
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert_with_asset() {
  expected="$1"
  input="$2"
  ./mycc "$input" > tmp.s
  cc -z noexecstack -c -o tmp.o tmp.s # -z noexecstack で何らかの警告を黙らせている
  cc -c -o asset.o asset.c
  cc -z noexecstack -o tmp tmp.o asset.o
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert_expr_with_asset() {

  expected="$1"
  input="$2"

  ./mycc "main() { return $input; }" > tmp.s
  cc -z noexecstack -c -o tmp.o tmp.s # -z noexecstack で何らかの警告を黙らせている
  cc -c -o asset.o asset.c
  cc -z noexecstack -o tmp tmp.o asset.o
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

# make && ./mycc "\
# main() {
#   return foo(23);
# }
# foo(a) {
#   return a;
# }" > tmp.s
# cc -z noexecstack -o tmp tmp.s
# ./tmp
# echo $?

# exit

assert_expr 0 "0"
assert_expr 42 "42"
assert_expr 21 "5+20-4"
assert_expr 32 "40 - 13 + 5"
assert_expr 47 '5+6*7'
assert_expr 15 '5*(9-6)'
assert_expr 4 '(3+5)/2'
assert_expr 6 '-2+(-2)+10'
assert_expr 1 '1 == 1'
assert_expr 1 '10 != 42'
assert_expr 0 "5 < 3"
assert_expr 1 "5 > 3"
assert_expr 1 "5 >= 3"
assert_expr 0 "5 <= 3"
assert_expr 1 "(0 == (0 + 3)) == 0"
assert_expr 3 "a = 3"
assert_stmts 30 "a = 3; b = 5; return (a + 3) * b;"
assert_stmts 42 "\
foo = 1;
z = 1;
return z - foo + 42;"
assert_stmts 14 "foo = 1; bar = 2; baz = 3; xxx = 4; return baz * xxx + foo * bar;"
assert_stmts 8 "return 8;"
assert_stmts 8 "return 8;\
return 4;"
assert_stmts 4 "\
if ( 1 == 1 )
  return 4;
return 3;"
assert_stmts 3 "\
if ( 1 == 0 )
  return 4;
return 3;"
assert_stmts 5 "\
if ( 1 == 0 )
  return 1;
if ( 1 == 0 )
  return 2;
if ( 1 == 0 )
  return 3;
if ( 1 == 0 )
  return 4;
return 5;"
assert_stmts 5 "\
if (1 == 0)
  return 3;
else
  return 5;"
assert_stmts 3 "\
if (1 != 0)
  return 3;
else
  return 5;"
assert_stmts 55 "\
a = 0;
b = 0;
while (a < 10)
  b = b + (a = a + 1);
return b;"
assert_stmts 6 "\
for (i = 0; i < 10; i = i + 1)
  if (i * i > 30)
    return i;
return 42;"
assert_stmts 42 "{ return 42; }"
assert_stmts 32 "\
{
  a = 4;
  b = a + 4;
  return a * b;
}"
assert_expr_with_asset 42 "foo()"
assert_expr_with_asset 0 "bar()"
assert_expr_with_asset 3 "mod4(7)"
assert_expr_with_asset 0 "potato(1, 2, 3, 4, 5, 6) - 321"
assert 42 "\
main() {
  return 42;
}"
assert 23 "\
main() {
  return foo(23);
}
foo(a) {
  return a;
}"
assert 120 "\
main() {
  return fact(5);
}
fact(a) {
  if (a == 0)
    return 1;
  return a * fact(a - 1);
}"
assert 233 "\
main() {
  return fib(13);
}
fib(a) {
  if (a == 0)
    return 0;
  if (a == 1)
    return 1;
  return fib(a-1) + fib(a-2);
}"
assert_with_asset 10 "\
main() {
  a = 10;
  b = &a;
  putnum(b);
  return *b;
}"
echo OK
