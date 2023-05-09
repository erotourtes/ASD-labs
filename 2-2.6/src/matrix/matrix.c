#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

int **mulmr(double k, double **matrix, int n);

Matrix get_undirected_matrix(Matrix m);

int **create_matrix(int n);

double **rand_matrix(int n);

void multiply_by_elements(Matrix target, Matrix m2);

void multiply_on(double scalar, double **m, int n);


Matrix get_boolean_matrix(int n, double k, unsigned int seed) {
    srand(seed);

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

Matrix init_matrix(int n) {
    return (Matrix) {create_matrix(n), n};
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
    Matrix new_matrix = init_matrix(m1.n);

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

void set_to_zero(Matrix m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            m.val[i][j] = 0;
        }
    }
}

void multiply_by_elements(Matrix target, Matrix m2) {
    for (int i = 0; i < m2.n; i++)
        for (int j = 0; j < m2.n; j++)
            target.val[i][j] *= m2.val[i][j];
}

void multiply_on(double scalar, double **m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] *= scalar;
}

Matrix get_matrix_B(Matrix W) {
    Matrix matrix = init_matrix(W.n);
    for (int i = 0; i < W.n; i++)
        for (int j = 0; j < W.n; j++)
            if (W.val[i][j] > 0)
                matrix.val[i][j] = 1;

    return matrix;
}

Matrix get_matrix_C(Matrix B) {
    Matrix matrix = init_matrix(B.n);
    for (int i = 0; i < B.n; i++)
        for (int j = 0; j < B.n; j++)
            if (B.val[i][j] != B.val[j][i])
                matrix.val[i][j] = 1;

    return matrix;
}

Matrix get_matrix_D(Matrix B) {
    Matrix matrix = init_matrix(B.n);
    for (int i = 0; i < B.n; i++)
        for (int j = 0; j < B.n; j++)
            if (B.val[i][j] == B.val[j][i] && B.val[i][j] == 1)
                matrix.val[i][j] = 1;

    return matrix;
}

Matrix get_Tr(int n) {
    Matrix matrix = init_matrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (j > i)
                matrix.val[i][j] = 1;

    return matrix;
}

Matrix get_Wt(Matrix A) {
    int n = A.n;
    double **randm = rand_matrix(n);
    multiply_on(100, randm, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            randm[i][j] *= A.val[i][j];

    Matrix wt = init_matrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            wt.val[i][j] = (int) round(randm[i][j]);

    for (int i = 0; i < n; i++)
        free(randm[i]);
    free(randm);

    return wt;
}

void symmetrise(Matrix m) {
    for (int i = 0; i < m.n; i++)
        for (int j = i + 1; j < m.n; j++)
            m.val[j][i] = m.val[i][j];
}

Matrix get_weights(Matrix A) {
    int n = A.n;
    Matrix wt = get_Wt(A);
    Matrix B = get_matrix_B(wt);
    Matrix C = get_matrix_C(B);
    Matrix D = get_matrix_D(B);
    Matrix Tr = get_Tr(n);

    multiply_by_elements(D, Tr);
    add_matrix(C, D);
    multiply_by_elements(wt, C);

    free_matrix(&B);
    free_matrix(&C);
    free_matrix(&D);
    free_matrix(&Tr);

    symmetrise(wt);

    return wt;;
}
