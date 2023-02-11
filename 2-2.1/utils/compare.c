#include <math.h>
#include <stdio.h>

#include "../loop.c"
#include "../recursionDepth.c"
#include "../recursionHeight.c"
#include "../recursionMixed.c"

#include "./types.c"

void compare() {
  u32 n = 5;

  printf("X\tCalculator\t\tDepth\t\t\tHeight\t\t\tMixed\t\t\tLoop\n");
  for (double x = 0; x < 1; x += 0.01) {
    printf("%.3lf\t", x);
    printf("%.15lf\t", asinh(x));
    printf("%.15lf\t", recursionDepth(x, n));
    printf("%.15lf\t", recursionHeight(x, n));
    printf("%.15lf\t", recursionMixed(x, n));
    printf("%.15lf\t", loop(x, n));
    printf("\n");
  }
}
