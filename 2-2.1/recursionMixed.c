#include "./utils/types.c"

double _recursionMixed(double x, u32 n, u32 i, double prev) {
  if (n == i)
    return 0;

  double current =
      prev * (-x * x * (2 * i - 1) * (2 * i - 1) / (4 * i * i + 2 * i));

  return current + _recursionMixed(x, n, i + 1, current);
}

double recursionMixed(double x, u32 n) {
  return _recursionMixed(x, n, 1, x) + x;
}

#define _recursionMixed call function
