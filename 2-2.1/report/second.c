#include <stdio.h>
#include <math.h>

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
         logs_recursionHeight(x, n));

  return 0;
}
