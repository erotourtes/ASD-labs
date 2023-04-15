#include "Matrix.h"
#include <stdlib.h>

int *get_degree(Matrix m);

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

void print_leaf_vertexes(const int *degree, int len) {
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


void print_isolated_vertexes(const int *degree, int n) {
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

Matrix multiply_matrix(const Matrix m1, const Matrix m2) {
    Matrix new_matrix = {create_matrix(m1.n), m1.n};

    for (int i = 0; i < m1.n; i++) {
        for (int j = 0; j < m1.n; j++) {
            for (int k = 0; k < m2.n; k++) {
                new_matrix.val[i][k] += m1.val[i][j] * m2.val[j][k];
            }
        }
    }

    return new_matrix;
}

// TODO: use dfs to find path with n edges
void path2(Matrix m) {
    Matrix square = multiply_matrix(m, m);
    printf("Square:\n");
    print_matrix(square, 0);

    printf("All paths of length 2:\n");
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            if (square.val[i][j] == 0) // find path from i to j through k
                continue;

            for (int k = 0; k < m.n; k++) {
                if (m.val[i][k] == 1 && m.val[k][j] == 1) {
                    printf("%d -> %d -> %d\n", i + 1, k + 1, j + 1);
                }
            }
        }
    }

    free_matrix(&square);
}

// TODO: use dfs to find path with n edges
void paths3(Matrix m) {
    Matrix square = multiply_matrix(m, m);
    Matrix cube = multiply_matrix(square, m);
    free_matrix(&square);
    printf("Cube:\n");
    print_matrix(cube, 0);

    printf("All paths of length 3:\n");
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            if (cube.val[i][j] == 0) // find path from i to j through k and l
                continue;

            for (int k = 0; k < m.n; k++) {
                for (int l = 0; l < m.n; l++) {
                    if (m.val[i][k] == 1 && m.val[k][l] == 1 && m.val[l][j] == 1) {
                        printf("%d -> %d -> %d -> %d\n", i + 1, k + 1, l + 1, j + 1);
                    }
                }
            }
        }
    }

    free_matrix(&cube);
}

void add_matrix(Matrix target, Matrix matrix) {
    for (int i = 0; i < target.n; i++) {
        for (int j = 0; j < target.n; j++) {
            target.val[i][j] += matrix.val[i][j];
        }
    }
}

void copy_matrix(Matrix target, Matrix matrix) {
    for (int i = 0; i < target.n; i++) {
        for (int j = 0; j < target.n; j++) {
            target.val[i][j] = matrix.val[i][j];
        }
    }
}

void to_boolean_matrix(Matrix m) {
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            if (m.val[i][j] != 0)
                m.val[i][j] = 1;
        }
    }
}

Matrix reachability_matrix(Matrix m) {
    Matrix cur = {create_matrix(m.n), m.n};
    copy_matrix(cur, m);

    Matrix reach = {create_matrix(m.n), m.n};
    for (int i = 0; i < m.n; i++)
        reach.val[i][i] = 1;

    for (int i = 0; i < m.n - 1; i++) {
        add_matrix(reach, cur);

        Matrix tmp = multiply_matrix(cur, m);
        free_matrix(&cur);
        cur = tmp;
    }

    to_boolean_matrix(reach);

    free_matrix(&cur);
    return reach;
}

void strongly_connected_components(Matrix m) {
    Matrix reach = reachability_matrix(m);

    // To avoid transposing matrix
    for (int i = 0; i < m.n; i++) {
        for (int j = 0; j < m.n; j++) {
            reach.val[i][j] = reach.val[i][j] & reach.val[j][i];
        }
    }


    printf("4.5\n");
    // Find components
    int *visited = calloc(m.n, sizeof(int));
    int cur_component = 0;
    for (int i = 0; i < m.n; i++) {
        if (visited[i] == 1)
            continue;

        printf("Component %d: ", ++cur_component);
        for (int j = 0; j < m.n; j++) {
            if (reach.val[i][j] == 1) {
                visited[j] = 1;
                printf("%d ", j + 1);
            }
        }

        printf("\n");
    }

    printf("4.6\n");
    printf("Matrix of strongly connected components:\n");
    print_matrix(reach, 0);

    printf("4.7\n");
    printf("Condensation graph:\n");



    free_matrix(&reach);
}

void do_lab_task4(Matrix m) {
    printf("#4\n");

    printf("%-30s", "Nodes:");
    for (int i = 0; i < m.n; i++)
        printf("%-2d ", i + 1);
    printf("\n");

    printf("4.2\n");
    int *in_degree = get_in_degree(m);
    printf("%-30s", "In-Degree of directed graph:");
    print_array(in_degree, m.n);
    free(in_degree);

    int *out_degree = get_out_degree(m);
    printf("%-30s", "Out-Degree of directed graph:");
    print_array(out_degree, m.n);
    free(out_degree);

    printf("4.3\n");
    path2(m);
    paths3(m);

    printf("4.4\n");
    Matrix reach = reachability_matrix(m);
    printf("Reachability matrix:\n");
    print_matrix(reach, 0);
    free_matrix(&reach);


    printf("4.5\n");
    strongly_connected_components(m);
}