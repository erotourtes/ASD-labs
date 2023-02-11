#include "./utils/types.c"

double loop(double x, u32 n) {
  double res = x;
  double current = x;

  for (u32 i = 1; i < n; i++) {
    current = current * (-x * x * (2 * i - 1) * (2 * i - 1) / (4 * i * i + 2 * i));
    res += current;
  }

  return res;
}
