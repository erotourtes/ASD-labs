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

void handle_key_press_p(X11 app, Matrix matrix, Point *coordinates, int circle_radius, int* current_edge, Edges edges);

void handle_key_press_n(int *current_edge, int count);

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

    Edges edges = bfs(matrix, 0);
    int current_edge = -1;

    while (1) {
        XNextEvent(app.dis, &event);
        // Expose event
        if (event.type == Expose && event.xexpose.count == 0) {
            redraw(app);
            draw_graph(app, matrix, coordinates, 1, circle_radius);
        }
        // KeyPress event
        if (event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
            if (text[0] == 'q')
                break;
            else if (text[0] == 'n')
                handle_key_press_n(&current_edge, edges.count);
            else if (text[0] == 'p')
                handle_key_press_p(app, matrix, coordinates, circle_radius, &current_edge, edges);

            if (current_edge == -1) continue;
            int from_node = edges.val[current_edge].from;
            int to_node = edges.val[current_edge].to;
            highlight_edge_between(app, matrix, coordinates, from_node, to_node, circle_radius);
        }
    }

    close_window(app);
    free_matrix(&matrix);
    free(coordinates);
    printf("Bye!");
    return 0;
}

Matrix set_right_matrix() {
    printf("\nGenerating matrix \n");
    double k = 1.0 - n3 * 0.01 - n4 * 0.005 - 0.15;
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
