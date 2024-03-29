//
// Created by sirmax on 4/27/23.
//

#ifndef INC_2_2_5_MATRIX_H
#define INC_2_2_5_MATRIX_H

typedef struct {
    int **val;
    int n;
} Matrix;

Matrix init_matrix(int n);

void free_matrix(Matrix *matrix);

void print_matrix(Matrix matrix, int should_print_undirected);

Matrix get_boolean_matrix(int n, double k, unsigned int seed);

void add_matrix(Matrix target, Matrix matrix);

Matrix get_weights(Matrix A);

Matrix get_undirected_matrix(Matrix m);

#endif //INC_2_2_5_MATRIX_H