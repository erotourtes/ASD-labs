#include <stdio.h>

#include "./types.c"

#include "./logs-loop.c"
#include "./logs-recursionDepth.c"
#include "./logs-recursionHeight.c"
#include "./logs-recursionMixed.c"

#include "./recursionDepth.c"
#include "./recursionHeight.c"
#include "./recursionMixed.c"

int main() {
  u32 n = 5;

  double x = 0;
  scanf("%lf", &x);

  if (x >= 1 || x <= -1) {
    printf("incorrect input");
    return 1;
  }

  printf("arsinh(%.2lf) = %*.7lf\n\n", x, 10, logs_loop(x, n));
  printf("arsinh(%.2lf) = %*.7lf\n\n", x, 10, logs_recursionDepth(x, n));
  printf("arsinh(%.2lf) = %*.7lf\n\n", x, 10, logs_recursionHeight(x, n));
  printf("arsinh(%.2lf) = %*.7lf\n\n", x, 10, logs_recursionMixed(x, n));

  printf("arsinh(%.2lf) = %*.7lf\n\n", x, 10, recursionDepth(x, n));
  printf("arsinh(%.2lf) = %*.7lf\n\n", x, 10, recursionHeight(x, n));
  printf("arsinh(%.2lf) = %*.7lf\n\n", x, 10, recursionMixed(x, n));

  return 0;
}
