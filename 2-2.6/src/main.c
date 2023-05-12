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
#include "prim's_alghoritm.c"
#include "graph/graph.h"

Matrix set_right_matrix();

int main() {
    X11 app = init("Lab #6");

    XEvent event;
    KeySym key;
    char text[255];

    int offset = 100;
    int circle_radius = 20;
    int distance = 150;

    printf("%s", n4 % 2 == 0 ? "Kruskal's algorithm\n" : "Prim's algorithm\n");

    Matrix matrix = set_right_matrix();
    Point *coordinates = get_coordinates(matrix.n, distance, offset, offset);

    Matrix weights = get_weights(matrix);
    print_matrix(weights, 0);

    while (1) {
        XNextEvent(app.dis, &event);
        // Expose event
        if (event.type == Expose && event.xexpose.count == 0) {
            redraw(app);
            draw_graph(app, matrix, weights, coordinates, 0, circle_radius);
        }
        // KeyPress event
        if (event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
            if (text[0] == 'q') break;
            if (text[0] == 's') {
                printf("Starting...\nPress <enter> button in the terminal emulator to continue\n");
                Graph g = get_graph_from(matrix, weights);
                minimum_spanning_tree(app, coordinates, g, matrix, circle_radius);
                printf("Done!\n");
                free_graph(&g);
            }
        }
    }

    close_window(app);
    free_matrix(&matrix);
    free(coordinates);
    free_matrix(&weights);
    printf("Bye!");
    return 0;
}

Matrix set_right_matrix() {
    printf("\nGenerating matrix \n");
    double k = 1.0 - n3 * 0.01 - n4 * 0.005 - 0.05;
    unsigned int seed = n1 * 1000 + n2 * 100 + n3 * 10 + n4;
    Matrix matrix = get_boolean_matrix(10 + n3, k, seed);
    Matrix m = get_undirected_matrix(matrix);
    print_matrix(m, 0);
    free_matrix(&matrix);

    return m;
}