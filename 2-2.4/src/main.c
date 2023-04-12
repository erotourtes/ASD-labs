// You need to install X11 library (sudo dnf install libX11-devel)

#define n1 2
#define n2 1
#define n3 1
#define n4 9

#include "app/app.c"
#include "matrix/graph_coords.c"
#include "matrix/matrix.c"
#include "app/draw_graph.c"

int main() {
    X11 app = init("Lab #3");

    XEvent event;
    KeySym key;
    char text[255];

    Matrix matrix = get_boolean_matrix(1.0 - n3 * 0.01 - n4 * 0.01 - 0.3);
    print_matrix(matrix, 1);
    print_matrix(matrix, 0);

    while (1) {
        XNextEvent(app.dis, &event);
        // Expose event
        if (event.type == Expose && event.xexpose.count == 0) {
            redraw(app);
        }
        // KeyPress event
        if (event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
            if (text[0] == 'q')
                break;

            redraw(app);
            if (text[0] == 'd')
                draw_graph(app, matrix, 1);
            else
                draw_graph(app, matrix, 0);
        }
    }

    close_window(app);
    free_matrix(matrix);
    printf("Bye!");
    return 0;
}