#include <stdio.h>

int foo(void) {
  return 42;
}

int bar(void) {
  printf("Hello!\n");
  return 0;
}

int fizzbuzz(int i) {
  if (i % 15 == 0)
    printf("fizzbuzz");
  else if (i % 5 == 0)
    printf("buzz");
  else if (i % 3 == 0)
    printf("fizz");
  else
    printf("%d", i);
}
