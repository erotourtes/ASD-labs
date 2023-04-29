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

int main() {
    X11 app = init("Lab #3");

    XEvent event;
    KeySym key;
    char text[255];

    int offset = 100;
    int circle_radius = 20;
    int distance = 150;

    Matrix matrix = set_right_matrix();
    Point *coordinates = get_coordinates(matrix.n, distance, 100, 100);

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
            if (text[0] == 'n') {
                if (current_edge + 1 < edges.count)
                    current_edge++;
            } else continue;

            int from_node = edges.val[current_edge].from;
            int to_node = edges.val[current_edge].to;
            printf("From %d to %d\n", from_node + 1, to_node + 1);
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