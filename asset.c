#include <stdio.h>

int foo(void) {
  return 42;
}

int bar(void) {
  printf("Hello!\n");
  return 0;
}

int mod4(int a) {
  return a % 4;
}

int potato(int a, int b, int c, int d, int e, int f) {
  return a + (b<<1) + (c<<2) + (d<<3) + (e<<4) + (f<<5);
}

void putnum(int a) {
  printf("%u\n", a);
}

// int fizzbuzz(int i) {
//   if (i % 15 == 0)
//     printf("fizzbuzz");
//   else if (i % 5 == 0)
//     printf("buzz");
//   else if (i % 3 == 0)
//     printf("fizz");
//   else
//     printf("%d", i);
// }
