#include <stdlib.h>
#include <stdio.h>

#define n1 2
#define n2 1
#define n3 1
#define n4 9

typedef struct {
    int **val;
    int n;
} Matrix;

int **rand_matrix(int n);

int **mulmr(double k, int **matrix, int n);

void free_matrix(Matrix matrix);

void print_matrix(Matrix matrix);

Matrix get_boolean_matrix() {
    srand(2119);

    int n = 10 + n3;
    int **matrix = rand_matrix(n);
    mulmr(1.0 - n3 * 0.02 - n4 * 0.005 - 0.25, matrix, n);

    return (Matrix){matrix, n};
}

int **rand_matrix(int n) {
    int **matrix = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 3;
        }
    }

    return matrix;
}

int **mulmr(double k, int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] * k > 1) matrix[i][j] = 1;
            else matrix[i][j] = 0;
        }
    }
}

void free_matrix(Matrix matrix) {
    for (int i = 0; i < matrix.n; i++)
        free(matrix.val[i]);
    free(matrix.val);
}

void print_matrix(Matrix matrix) {
    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.n; j++) {
            printf("%d ", matrix.val[i][j]);
        }
        printf("\n");
    }
}