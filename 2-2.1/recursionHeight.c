#include "./utils/types.c"

double _recursionHeight(double x, u32 n, double *res) {
  if (n == 0)
    return x;

  double current = _recursionHeight(x, n - 1, res) *
                   (-x * x * (2 * n - 1) * (2 * n - 1) / (4 * n * n + 2 * n));
  *res = *res + current;

  return current;
}

double recursionHeight(double x, u32 n) {
  double result = x;
  _recursionHeight(x, n - 1, &result);

  return result;
}

#define _recursionHeight call function
