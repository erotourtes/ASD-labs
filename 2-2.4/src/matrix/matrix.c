#include <stdlib.h>
#include <stdio.h>
#include "Matrix.h"

int **rand_matrix(int n);

int **mulmr(double k, int **matrix, int n);

void free_matrix(Matrix *matrix);

void print_matrix(Matrix matrix);

Matrix get_boolean_matrix(int n, double k) {
    srand(n1 * 1000 + n2 * 100 + n3 * 10 + n4);

    int **matrix = rand_matrix(n);
    mulmr(k, matrix, n);

    return (Matrix) {matrix, n};
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

void free_matrix(Matrix *matrix) {
    if (matrix->val == NULL)
        return;

    for (int i = 0; i < matrix->n; i++)
        free(matrix->val[i]);
    free(matrix->val);

    matrix->val = NULL;
}

Matrix get_undirected_matrix(Matrix m) {
    int **matrix = (int **) malloc(m.n * sizeof(int *));
    for (int i = 0; i < m.n; i++) {
        matrix[i] = (int *) malloc(m.n * sizeof(int));
        for (int j = 0; j < m.n; j++) {
            matrix[i][j] = m.val[i][j] | m.val[j][i];
        }
    }

    return (Matrix) {matrix, m.n};
}

void print_matrix(Matrix matrix) {
    Matrix undirected = get_undirected_matrix(matrix);
    printf("Matrix:\t\t\tUndirected matrix:\n");
    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.n; j++)
            printf("%d ", matrix.val[i][j]);

        printf("\t");

        for (int j = 0; j < matrix.n; j++)
            printf("%d ", undirected.val[i][j]);

        printf("\n");
    }

    free_matrix(&undirected);
}