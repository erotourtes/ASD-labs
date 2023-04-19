// You need to install X11 library (sudo dnf install libX11-devel)

#define n1 2
#define n2 1
#define n3 1
#define n4 9

#include "app/app.c"
#include "matrix/matrix.c"
#include "app/draw_graph.c"
#include "matrix/graph_characteristics.c"

int main() {
    X11 app = init("Lab #3");

    XEvent event;
    KeySym key;
    char text[255];

    Matrix matrix = {NULL, 0};

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

            if (text[0] == '1' || matrix.val == NULL) {
                printf("\nGenerating matrix 1...\n");
                free_matrix(&matrix);
                matrix = get_boolean_matrix(10 + n3, 1.0 - n3 * 0.01 - n4 * 0.01 - 0.3);
                print_matrix(matrix, 1);
                do_lab_task1(matrix);
            } else if (text[0] == '2') {
                printf("\nGenerating matrix 2...\n");
                free_matrix(&matrix);
                matrix = get_boolean_matrix(10 + n3, 1.0 - n3 * 0.005 - n4 * 0.005 - 0.27);
                print_matrix(matrix, 0);
                do_lab_task4(matrix);
            }

            int is_directed = text[0] == 'u' ? 0 : 1;
            redraw(app);
            draw_graph(app, matrix, is_directed);
        }
    }

    close_window(app);
    free_matrix(&matrix);
    printf("Bye!");
    return 0;
}