#include "./types.c"
#include <stdio.h>

double _recursionDepth(double x, u32 n, u32 i, double prev, double res) {
  if (n == i)
    return res;

  prev = prev * (-x * x * (2 * i - 1) * (2 * i - 1) / (4 * i * i + 2 * i));
  res += prev;

  return _recursionDepth(x, n, i + 1, prev, res);
}

double recursionDepth(double x, u32 n) {
  return _recursionDepth(x, n, 1, x, x);
}

#define _recursionDepth call function
