#include "./types.c"
#include <stdio.h>

double _logs_recursionDepth(double x, u32 n, u32 i, double prev, double res) {
  if (n == i) {
    return res;
  }

  if (i == 1)
    printf("i: %*d;\t prev: %*lf; \tres: %*lf\n", 5, i, 5, prev, 5, res);

  prev = prev * (-x * x * (2 * i - 1) * (2 * i - 1) / (4 * i * i + 2 * i));
  res += prev;

  printf("i: %*d;\t prev: %*lf; \tres: %*lf\n", 5, i + 1, 5, prev, 5, res);

  double tmp = _logs_recursionDepth(
      x, n, i + 1, prev,
      res); // Created this variable to print that we are going up

  printf("i: %*d; \t Going up \n", 5, i);

  return tmp;
}

double logs_recursionDepth(double x, u32 n) {
  return _logs_recursionDepth(x, n, 1, x, x);
}

#define _logs_recursionDepth call function
