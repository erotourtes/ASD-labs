#include "./types.c"
#include <stdio.h>

double _logs_recursionHeight(double x, u32 n, double *res) {
  if (n == 0) {
    printf("i: %*d;\t prev: %*lf; \tres: %*lf\n", 5, n + 1, 5, x, 5, x);
    return x;
  }

  printf("i: %*d; \t Going down \n", 5, n);

  double prev = _logs_recursionHeight(x, n - 1, res) *
                (-x * x * (2 * n - 1) * (2 * n - 1) / (4 * n * n + 2 * n));
  *res = *res + prev;

  printf("i: %*d;\t prev: %*lf; \tres: %*lf\n", 5, n + 1, 5, prev, 5, *res);

  return prev;
}

double logs_recursionHeight(double x, u32 n) {
  double result = x;
  _logs_recursionHeight(x, n - 1, &result);

  return result;
}

#define _logs_recursionHeight call function
