#include "Matrix.h"
#include <stdlib.h>

#define NULL 0

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
    int *in_degree = get_in_degree(m);
    int *out_degree = get_out_degree(m);

    int regularity = 0;
    for (int i = 1; i < m.n; i++) {
        if (in_degree[i] != in_degree[i - 1] || out_degree[i] != out_degree[i - 1] || in_degree[i] != out_degree[i]) {
            regularity = -1;
            break;
        }
        regularity++;
    }

    free(in_degree);
    free(out_degree);
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

    int regular = get_regularity(u_m);
    printf("Undirected ");
    printf("%-30s", regular == -1 ? "Graph is irregular" : "Graph is regular:");
    printf("%d\n", regular);

    regular = get_regularity(m);
    printf("Directed ");
    printf("%-30s", regular == -1 ? "Graph is irregular" : "Graph is regular:");
    printf("%d\n", regular);

    printf("#3\n");

    printf("%-30s", "Leaf vertexes:");
    print_leaf_vertexes(degree, m.n);

    printf("%-30s", "Isolated vertexes:");
    print_isolated_vertexes(degree, m.n);
    free(degree);

    free_matrix(&u_m);
}

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

void paths3(Matrix m) {
    // might use paths2 not to calculate square matrix twice and get rid of 4x loop,
    // however it wouldn't be independent function and I need to implement List, so I decided to leave it as is
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
                    if (m.val[i][k] && m.val[k][l] && m.val[l][j]) {
                        printf("%d -> %d -> %d -> %d\n", i + 1, k + 1, l + 1, j + 1);
                    }
                }
            }
        }
    }

    free_matrix(&cube);
}

void paths_recursive(int len, int cur_paths_count, int *path, const Matrix m) {
    // might be memoized
    if (len == cur_paths_count)
        return print_array(path, len);

    for (int i = 0; i < m.n; i++) {
        int last_node = path[cur_paths_count - 1];
        if (m.val[last_node][i]) {
            path[cur_paths_count++] = i;
            paths_recursive(len, cur_paths_count, path, m);
            cur_paths_count--;
        }
    }
}

void print_paths(int n, Matrix m) {
    int num_of_nodes = n + 1;
    int *path = calloc(num_of_nodes, sizeof(int));
    for (int i = 0; i < num_of_nodes; i++) {
        path[0] = i;
        paths_recursive(num_of_nodes, 1, path, m);
    }
    free(path);
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

Matrix strongly_connected_matrix(const Matrix m) {
    Matrix reach = reachability_matrix(m);

    // To avoid transposing matrix
    for (int i = 0; i < m.n; i++)
        for (int j = 0; j < m.n; j++)
            reach.val[i][j] = reach.val[i][j] & reach.val[j][i];

    return reach;
}

int **strongly_connected_components(Matrix reach) {
    int *visited = calloc(reach.n, sizeof(int));
    int **components = calloc(reach.n + 1, sizeof(int *));
    int size = 0;
    for (int i = 0; i < reach.n; i++) {
        if (visited[i] == 1)
            continue;

        int *component = calloc(reach.n + 1, sizeof(int));
        int component_size = 0;
        for (int j = 0; j < reach.n; j++) {
            if (reach.val[i][j] == 1) {
                component[component_size++] = j;
                visited[j] = 1;
            }
        }

        // marker to indicate end of component
        component[component_size] = -1;
        components[size++] = component;
    }

    components[size] = NULL;

    free(visited);
    return components;
}

void print_components(int **components) {
    printf("Strongly connected components:\n");
    for (int i = 0; components[i] != NULL; i++) {
        printf("Component %d: ", i + 1);
        for (int j = 0; components[i][j] != -1; j++) {
            printf("%d ", components[i][j] + 1);
        }
        printf("\n");
    }
}

Matrix get_condensation_graph(Matrix m, int **components) {
    int size = 0;
    while (components[size] != NULL) size++;
    /*
     *  Representation of component
     *  0: 1 4 6 -1
     *  1: 0 2 5 -1
     *  2: 7 -1
     *  NULL
     *
     *  where 0, 1, 2 are indexes of components
     *  and 1, 4, 6 are nodes that create a component
     *  -1 and NULL are markers to indicate end of component
     * */

    Matrix condensation = {create_matrix(size), size};
    for (int i = 0; components[i] != NULL; i++) {
        for (int j = 0; components[i][j] != -1; j++) {
            int cur_node = components[i][j];

            for (int k = 0; k < size; k++) {
                if (i == k)
                    continue;

                for (int l = 0; components[k][l] != -1; l++) {
                    int next_component_node = components[k][l];

                    if (m.val[cur_node][next_component_node] == 1) {
                        condensation.val[i][k] = 1;
                    }
                }
            }
        }
    }

    return condensation;
}

Matrix do_lab_task4(Matrix m) {
    printf("#4\n");

    printf("4.2\n");
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

    printf("4.3\n");
    path2(m);
    paths3(m);
//    print_paths(2, m);

    printf("4.4\n");
    Matrix reach = reachability_matrix(m);
    printf("Reachability matrix:\n");
    print_matrix(reach, 0);
    free_matrix(&reach);

    printf("4.5\n");
    Matrix strongly_connected = strongly_connected_matrix(m);
    int **components = strongly_connected_components(strongly_connected);
    print_components(components);

    printf("4.6\n");
    printf("Matrix of strongly connected components:\n");
    print_matrix(strongly_connected, 0);
    free_matrix(&strongly_connected);

    printf("4.7\n");
    printf("Condensation graph:\n");
    Matrix condensation = get_condensation_graph(m, components);
    print_matrix(condensation, 0);

    for (int i = 0; components[i] != NULL; i++)
        free(components[i]);
    free(components);

    return condensation;
}