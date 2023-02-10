#include <stdio.h>

#include "./types.c"
#include "./loop.c"
#include "./recursionDepth.c"
#include "./recursionHeight.c"


int main() {
  u32 n = 5;

  double x = 0;
  scanf("%lf", &x);

  if (x >= 1 || x <= -1) {
    printf("incorrect input");
    return 1;
  }

  printf("arsinh(%.2lf) = %*.7lf", x, 10, loop(x, n));
  // printf("arsinh(%.2lf) = %*.7lf", x, 10, recursionDepth(x, n));
  printf("arsinh(%.2lf) = %*.7lf", x, 10, recursionHeight(x, n));

  return 0;
}
