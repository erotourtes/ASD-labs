#include "./types.c"
#include <stdio.h>

double _recursionMixed(double x, u32 n, u32 i, double prev) {
  double res = 0;

  if (i == 1)
    printf("i: %*d;\t prev: %*lf; \tres: %*lf\n", 5, i, 5, prev, 5, res);

  if (n == i) {
    printf("i: %*d;\t Going up \n", 5, i);
    return 0;
  }

  double current = prev * (-x * x * (2 * i - 1) * (2 * i - 1) / (4 * i * i + 2 * i));

  printf("i: %*d;\t current: %*lf; \tres: %*lf\n", 5, i + 1, 5, current, 5, res);

  res = current + _recursionMixed(x, n, i + 1, current);

  printf("i: %*d;\t current: %*lf; \tres: %*lf\n", 5, i + 1, 5, current, 5, res);

  return res;
}

double recursionMixed(double x, u32 n) {
  return _recursionMixed(x, n, 1, x) + x;
}

#define _recursionHeight call function
