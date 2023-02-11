#include "./types.c"
#include <stdio.h>

double _recursionHeight(double x, u32 n, double *res) {
  if (n == 0)
    return x;

  double prev = _recursionHeight(x, n - 1, res) *
                (-x * x * (2 * n - 1) * (2 * n - 1) / (4 * n * n + 2 * n));
  *res = *res + prev;

  return prev;
}

double recursionHeight(double x, u32 n) {
  double result = x;
  _recursionHeight(x, n - 1, &result);

  return result;
}

#define _recursionHeight call function
