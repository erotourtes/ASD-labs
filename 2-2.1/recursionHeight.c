#include <stdio.h>
#include "./types.c"

double _recursionHeight(double x, u32 n, u32 i, double prev, double res) {
    return 0;
}

double recursionHeight(double x, u32 n) {
    return _recursionHeight(x, n, 1, x, x);
}

#define _recursionHeight call function
