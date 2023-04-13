#include "Matrix.h"
#include <stdlib.h>

int *get_degree(Matrix m) {
    int *degree = (int *) malloc(m.n * sizeof(int));
    for (int i = 0; i < m.n; i++) {
        degree[i] = 0;
        for (int j = 0; j < m.n; j++) {
            if (i == j)
                degree[i] += m.val[i][j] + m.val[j][i];
            else
                degree[i] += m.val[i][j] | m.val[j][i];
        }
    }

    return degree;
}

int *get_in_degree(Matrix m) {
    int *degree = (int *) malloc(m.n * sizeof(int));
    for (int i = 0; i < m.n; i++) {
        degree[i] = 0;
        for (int j = 0; j < m.n; j++) {
            degree[i] += m.val[j][i];
        }
    }

    return degree;
}

int *get_out_degree(Matrix m) {
    int *degree = (int *) malloc(m.n * sizeof(int));
    for (int i = 0; i < m.n; i++) {
        degree[i] = 0;
        for (int j = 0; j < m.n; j++) {
            degree[i] += m.val[i][j];
        }
    }

    return degree;
}

// if graph is regular, return degree of graph else return -1
int get_regularity(Matrix m) {
    int *degree = get_degree(m);

    int regularity = 0;
    for (int i = 1; i < m.n; i++) {
        if (degree[i] != degree[i - 1]) {
            regularity = -1;
            break;
        }
        regularity++;
    }

    free(degree);
    return regularity;
}

void print_leaf_vertexes(int *degree, int len) {
    for (int i = 0; i < len; i++) {
        if (degree[i] == 1)
            printf("%d ", i + 1);
    }
    printf("\n");
}

void print_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%-2d ", arr[i]);
    }
    printf("\n");
}


void print_isolated_vertexes(int *degree, int n) {
    for (int i = 0; i < n; i++) {
        if (degree[i] == 0)
            printf("%d ", i + 1);
    }
    printf("\n");
}

void do_lab_task1(Matrix m) {
    Matrix u_m = get_undirected_matrix(m);

    printf("#2\n");

    printf("%-30s", "Nodes:");
    for (int i = 0; i < m.n; i++)
        printf("%-2d ", i + 1);
    printf("\n");

    int *degree = get_degree(u_m);
    printf("%-30s", "Degree of graph:");
    print_array(degree, m.n);

    int *in_degree = get_in_degree(m);
    printf("%-30s", "In-Degree of directed graph:");
    print_array(in_degree, m.n);
    free(in_degree);

    int *out_degree = get_out_degree(m);
    printf("%-30s", "Out-Degree of directed graph:");
    print_array(out_degree, m.n);
    free(out_degree);

    // is same for directed and undirected graph
    int regular = get_regularity(u_m);
    printf("%-30s", regular == -1 ? "Graph is irregular" : "Graph is regular:");
    printf("%d\n", regular);

    printf("#3\n");

    // is same for directed and undirected graph
    printf("%-30s", "Leaf vertexes:");
    print_leaf_vertexes(degree, m.n);

    printf("%-30s", "Isolated vertexes:");
    print_isolated_vertexes(degree, m.n);
    free(degree);
}

int path2(Matrix m) {

}


void do_lab_task4(Matrix m) {
    printf("#4\n");

    printf("%-30s", "Nodes:");
    for (int i = 0; i < m.n; i++)
        printf("%-2d ", i + 1);
    printf("\n");

    int *in_degree = get_in_degree(m);
    printf("%-30s", "In-Degree of directed graph:");
    print_array(in_degree, m.n);
    free(in_degree);

    int *out_degree = get_out_degree(m);
    printf("%-30s", "Out-Degree of directed graph:");
    print_array(out_degree, m.n);
    free(out_degree);
}