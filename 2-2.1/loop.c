#include <stdio.h>
#include "./types.c"

double loop(double x, u32 n) {
  double res = x;
  double prev = x;
  printf("i: %*d;\t prev: %*lf; \tres: %*lf\n", 5, 1, 5, prev, 5, res);

  for (u32 i = 1; i < n; i++) {
    prev = prev * (-x * x * (2 * i - 1) * (2 * i - 1) / (4 * i * i + 2 * i));
    res += prev;

    printf("i: %*d;\t prev: %*lf; \tres: %*lf\n", 5, i + 1, 5, prev, 5, res);
  }

  return res;
}
