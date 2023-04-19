#include <stdio.h>
#include <stdlib.h>

#define n1 2
#define n2 1
#define n3 1
#define n4 9

typedef struct {
  int **val;
  int n;
} Matrix;

double **rand_matrix(int n);

int **mulmr(double k, double **matrix, int n);

void free_matrix(Matrix matrix);

void print_matrix(Matrix matrix, int is_directed);

Matrix get_boolean_matrix() {
  srand(n1 * 1000 + n2 * 100 + n3 * 10 + n4);

  int n = 10 + n3;
  double **matrix = rand_matrix(n);
  int ** boolean_matrix = mulmr(1.0 - n3 * 0.02 - n4 * 0.005 - 0.25, matrix, n);

  for (int i = 0; i < n; i++)
    free(matrix[i]);
  free(matrix);

  return (Matrix){boolean_matrix, n};
}

double **rand_matrix(int n) {
  double **matrix = (double **)malloc(n * sizeof(double *));
  for (int i = 0; i < n; i++) {
    matrix[i] = (double *)malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
      matrix[i][j] = 2.0 * rand() / RAND_MAX;
    }
  }

  return matrix;
}

int **mulmr(double k, double **matrix, int n) {
  int **result = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++)
    result[i] = (int *)malloc(n * sizeof(int));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
        result[i][j] = matrix[i][j] * k;

  return result;
}

void free_matrix(Matrix matrix) {
  for (int i = 0; i < matrix.n; i++)
    free(matrix.val[i]);
  free(matrix.val);
}

void print_matrix(Matrix matrix, int is_directed) {
  for (int i = 0; i < matrix.n; i++) {
    for (int j = 0; j < matrix.n; j++) {
      if (is_directed)
        printf("%d ", matrix.val[i][j]);
      else
        printf("%d ", matrix.val[i][j] | matrix.val[j][i]);
    }
    printf("\n");
  }

  printf("\n");
}
