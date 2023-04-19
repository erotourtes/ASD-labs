#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Matrix.h"

double **rand_matrix(int n);

int **mulmr(double k, double **matrix, int n);

void free_matrix(Matrix *matrix);

void print_matrix(Matrix matrix, int should_print_undirected);

Matrix get_boolean_matrix(int n, double k) {
    srand(n1 * 1000 + n2 * 100 + n3 * 10 + n4);

    double **matrix = rand_matrix(n);
    int **boolean_matrix = mulmr(k, matrix, n);

    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);

    return (Matrix) {boolean_matrix, n};
}

int **create_matrix(int n) {
    int **matrix = (int **) malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        matrix[i] = (int *) calloc(n, sizeof(int));

    return matrix;
}

double **rand_matrix(int n) {
    double **matrix = (double **) malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double *) malloc(n * sizeof(double));
        for (int j = 0; j < n; j++)
            matrix[i][j] = 2.0 * rand() / RAND_MAX;
    }

    return matrix;
}

int **mulmr(double k, double **matrix, int n) {
    int **boolean_matrix = create_matrix(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            boolean_matrix[i][j] = matrix[i][j] * k;

    return boolean_matrix;
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

void print_matrix(Matrix matrix, int should_print_undirected) {
    Matrix undirected = get_undirected_matrix(matrix);

    char undirected_str[] = "\t\t\tUndirected matrix:";
    char str[30] = "Matrix:";
    if (should_print_undirected)
        strcat(str, undirected_str);
    printf("%s \n", str);

    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.n; j++)
            printf("%d ", matrix.val[i][j]);

        if (!should_print_undirected) {
            printf("\n");
            continue;
        }

        printf("\t");

        for (int j = 0; j < matrix.n; j++)
            printf("%d ", undirected.val[i][j]);

        printf("\n");
    }

    free_matrix(&undirected);
}

Matrix multiply_matrix(const Matrix m1, const Matrix m2) {
    Matrix new_matrix = {create_matrix(m1.n), m1.n};

    for (int i = 0; i < m1.n; i++)
        for (int j = 0; j < m1.n; j++)
            for (int k = 0; k < m2.n; k++)
                new_matrix.val[i][k] += m1.val[i][j] * m2.val[j][k];

    return new_matrix;
}


void add_matrix(Matrix target, const Matrix matrix) {
    for (int i = 0; i < target.n; i++)
        for (int j = 0; j < target.n; j++)
            target.val[i][j] += matrix.val[i][j];
}

void copy_matrix(Matrix target, const Matrix matrix) {
    for (int i = 0; i < target.n; i++)
        for (int j = 0; j < target.n; j++)
            target.val[i][j] = matrix.val[i][j];
}

void to_boolean_matrix(Matrix m) {
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.n; j++)
            if (m.val[i][j] != 0)
                m.val[i][j] = 1;
}
