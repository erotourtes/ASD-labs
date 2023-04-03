// You need to install X11 library (sudo dnf install libX11-devel)

#include <stdio.h>
#include <math.h>

#include "./Point.h"
#include "./app.c"
#include "./matrix.c"
#include "./graph_coords.c"
#include "./draw_graph.c"

int main() {
    X11 app = init("Lab #3");

    XEvent event;
    KeySym key;
    char text[255];

    Matrix matrix = get_boolean_matrix();
    print_matrix(matrix);

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
            draw_graph(app, matrix);
        }
    }

    close_window(app);
    free_matrix(matrix);
    printf("Bye!");
    return 0;
}