#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

int test_id = 0;
int is_failed = 0;
void test(char *msg, int expr, int expected) {
  if (expr == expected) {
    printf("%s(%d): ok\n", msg, test_id);
  } else {
    printf("%s(%d): expr != expected (%d != %d)\n", msg, test_id, expr, expected);
    is_failed = 1;
  } 
  test_id++;
}

void end_test() {
  exit(is_failed);
}

// int param2(int a, int b) {
//   printf("(%d, %d)\n", a, b);
//   return a + b;
// }

// int param3(int a, int b, int c) {
//   printf("(%d, %d, %d)\n", a, b, c);
//   return a + b + c;
// }