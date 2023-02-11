#include <stdio.h>
#include "./types.c"

double _recursionHeight(double x, u32 n, double* res) {
    if (n == 0) {
        printf("i: %*d;\t prev: %*lf; \tres: %*lf\n", 5, n + 1, 5, x, 5, x);
        return x;
    }

    printf("i: %*d; \t Going down \n", 5, n);

    double prev = _recursionHeight(x, n-1, res) * (-x * x * (2 * n - 1) * (2 * n - 1) / (4 * n * n + 2 * n));
    *res = *res + prev;

    printf("i: %*d;\t prev: %*lf; \tres: %*lf\n", 5, n + 1, 5, prev, 5, *res);

    return prev;
}

double recursionHeight(double x, u32 n) {
    double result = x;
    _recursionHeight(x, n-1, &result);

    return result;
}

#define _recursionHeight call function
