#include <math.h>
#include <stdio.h>

typedef unsigned int u32;

double logs_loop(double x, u32 n) {
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

double _logs_recursionMixed(double x, u32 n, u32 i, double prev) {
  double res = 0;

  if (i == 1)
    printf("i: %*d;\t prev: %*lf; \tres: %*lf\n", 5, i, 5, prev, 5, res);

  if (n == i) {
    printf("i: %*d;\t Going up \n", 5, i);
    return 0;
  }

  double current =
      prev * (-x * x * (2 * i - 1) * (2 * i - 1) / (4 * i * i + 2 * i));

  printf("i: %*d;\t current: %*lf; \tres: %*lf\n", 5, i + 1, 5, current, 5,
         res);

  res = current + _logs_recursionMixed(x, n, i + 1, current);

  printf("i: %*d;\t current: %*lf; \tres: %*lf\n", 5, i + 1, 5, current, 5,
         res);

  return res;
}

double logs_recursionMixed(double x, u32 n) {
  return _logs_recursionMixed(x, n, 1, x) + x;
}

int main() {
  u32 n = 5;

  double x = 0;
  scanf("%lf", &x);

  if (x >= 1 || x <= -1) {
    printf("incorrect input");
    return 1;
  }

  printf("calc:      arsinh(%.2lf) = %*.7lf\n\n", x, 10, asinh(x));
  printf("loop:      arsinh(%.2lf) = %*.7lf\n\n", x, 10, logs_loop(x, n));
  printf("recursion: arsinh(%.2lf) = %*.7lf\n\n", x, 10,
         logs_recursionMixed(x, n));

  return 0;
}
