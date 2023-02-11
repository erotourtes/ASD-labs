#include <stdio.h>

#include "./logs-functions/logs-loop.c"
#include "./logs-functions/logs-recursionDepth.c"
#include "./logs-functions/logs-recursionHeight.c"
#include "./logs-functions/logs-recursionMixed.c"

#include "./utils/compare.c"

int main() {
  // u32 n = 5;
  //
  // double x = 0;
  // scanf("%lf", &x);
  //
  // if (x >= 1 || x <= -1) {
  //   printf("incorrect input");
  //   return 1;
  // }
  //
  // printf("arsinh(%.2lf) = %*.7lf\n\n", x, 10, logs_loop(x, n));
  // printf("arsinh(%.2lf) = %*.7lf\n\n", x, 10, logs_recursionDepth(x, n));
  // printf("arsinh(%.2lf) = %*.7lf\n\n", x, 10, logs_recursionHeight(x, n));
  // printf("arsinh(%.2lf) = %*.7lf\n\n", x, 10, logs_recursionMixed(x, n));

  compare();

  return 0;
}
