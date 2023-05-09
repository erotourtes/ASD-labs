// You need to install X11 library (sudo dnf install libX11-devel)

#define n1 2
#define n2 1
#define n3 1
#define n4 9

#include <X11/Xutil.h>
#include "app/app.h"
#include "drawing/draw_graph.h"
#include "drawing/graph_coords.h"
#include "matrix/matrix.h"
#include "traversal_algorithms.c"

Matrix set_right_matrix();

void handle_key_press_p(X11 app, Matrix matrix, Point *coordinates, int circle_radius, int *current_edge, Edges edges);

void handle_key_press_n(int *current_edge, int count);

void print_edges(Edges edges, Matrix matrix);

void print_order_list(Edges edges);

Edges change_component(Edges edges, Matrix matrix, Matrix visited, X11 app, Point *coordinates, int circle_radius,
                       int *current_edge, Edges (*traversal_function)(Matrix, int));

void print_task_result(Edges edges, Matrix matrix);

int main() {
    X11 app = init("Lab #3");

    XEvent event;
    KeySym key;
    char text[255];

    int offset = 100;
    int circle_radius = 20;
    int distance = 150;

    Matrix matrix = set_right_matrix();
    Point *coordinates = get_coordinates(matrix.n, distance, offset, offset);

    Matrix weights = get_weights(matrix);
    print_matrix(weights, 0);
    free_matrix(&weights);


    Matrix visited = init_matrix(matrix.n);

    Edges (*traversal_function)(Matrix, int) = &bfs;
    Edges edges = traversal_function(matrix, 0);
    int current_edge = -1;
    print_task_result(edges, matrix);

    while (1) {
        XNextEvent(app.dis, &event);
        // Expose event
        if (event.type == Expose && event.xexpose.count == 0) {
            redraw(app);
            draw_graph(app, matrix, coordinates, 1, circle_radius);
        }
        // KeyPress event
        if (event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
            if (text[0] == 'q') break;
            else if (text[0] == 'n') handle_key_press_n(&current_edge, edges.count); // next for current traversal
            else if (text[0] == 'c') {
                edges = change_component(edges, matrix, visited, app, coordinates, circle_radius, &current_edge,
                                         traversal_function);
                print_task_result(edges, matrix);

            } else if (text[0] == 'p')
                handle_key_press_p(app, matrix, coordinates, circle_radius, &current_edge, edges);
            else if (text[0] == 's') {
                redraw(app);
                draw_graph(app, matrix, coordinates, 1, circle_radius);
                if (traversal_function == &bfs) traversal_function = &dfs;
                else traversal_function = &bfs;
                free(edges.val);
                edges.val = NULL;
                edges = traversal_function(matrix, 0);
                current_edge = -1;
                print_task_result(edges, matrix);
                set_to_zero(visited);
            }

            if (current_edge == -1) continue;
            int from_node = edges.val[current_edge].from;
            int to_node = edges.val[current_edge].to;
            highlight_edge_between(app, matrix, coordinates, from_node, to_node, circle_radius);
        }
    }

    close_window(app);
    free_matrix(&matrix);
    free_matrix(&visited);
    free(edges.val);
    free(coordinates);
    printf("Bye!");
    return 0;
}

void print_task_result(Edges edges, Matrix matrix) {
    printf("\n\nTask result(for %d): \n", edges.val[0].from + 1);
    printf("Order list: \t");
    print_order_list(edges);
    printf("\nEdges: \n");
    print_edges(edges, matrix);
}

// Bloated code, but it's ok for now
Edges change_component(Edges edges, Matrix matrix, Matrix visited, X11 app, Point *coordinates, int circle_radius,
                       int *current_edge, Edges (*traversal_function)(Matrix, int)) {
    // Mark all visited nodes
    for (int k = 0; k < edges.count; k++) {
        int from = edges.val[k].from;
        int to = edges.val[k].to;
        if (from == to) visited.val[from][to] = 1;
    }

    // Find unvisited node
    int unvisited_node = -1;
    for (int i = 0; i < matrix.n; i++) {
        if (unvisited_node != -1) break;
        unvisited_node = i;
        for (int j = 0; j < matrix.n; j++) {
            if (visited.val[i][j] == 1) {
                unvisited_node = -1;
                break;
            }
        }
    }

    if (unvisited_node == -1) {
        set_to_zero(visited);
        return edges;
    }

    free(edges.val);
    edges.val = NULL;
    printf("\nNew component: %d\n", unvisited_node + 1);
    *current_edge = -1;
    redraw(app);
    draw_graph(app, matrix, coordinates, 1, circle_radius);

    return traversal_function(matrix, unvisited_node);
}

Matrix set_right_matrix() {
    printf("\nGenerating matrix \n");
    double k = 1.0 - n3 * 0.01 - n4 * 0.005 - 0.05;
    unsigned int seed = n1 * 1000 + n2 * 100 + n3 * 10 + n4;
    Matrix matrix = get_boolean_matrix(10 + n3, k, seed);
    print_matrix(matrix, 1);

    return matrix;
}

void handle_key_press_p(X11 app, Matrix matrix, Point *coordinates, int circle_radius, int *current_edge, Edges edges) {
    redraw(app);
    draw_graph(app, matrix, coordinates, 1, circle_radius);
    if (*current_edge > -1) (*current_edge)--;
    for (int i = 0; i < *current_edge; i++) {
        int from_node = edges.val[i].from;
        int to_node = edges.val[i].to;
        highlight_edge_between(app, matrix, coordinates, from_node, to_node, circle_radius);
    }
}

void handle_key_press_n(int *current_edge, int count) {
    if (*current_edge + 1 < count)
        (*current_edge)++;
}

void print_edges(const Edges edges, const Matrix matrix) {
    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.n; j++) {
            int is_edge = 0;
            for (int k = 0; k < edges.count; k++) {
                if (edges.val[k].from == i && edges.val[k].to == j && i != j) {
                    is_edge = 1;
                    break;
                }
            }
            printf("%d ", is_edge);
        }
        printf("\n");
    }
}

void print_order_list(Edges edges) {
    int counter = 1;
    for (int i = 0; i < edges.count; i++) {
        Edge ed = edges.val[i];
        if (ed.from == ed.to) printf("%d: %d \t", counter++, ed.to + 1);
    }
    printf("\n");
}