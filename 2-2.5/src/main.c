// You need to install X11 library (sudo dnf install libX11-devel)

#define n1 2
#define n2 1
#define n3 1
#define n4 9

#include "app/app.c"
#include "matrix/matrix.c"
#include "app/draw_graph.c"
#include "matrix/traversal_algorithms.c"

void handle_button_pressed1(Matrix *matrix);

void handle_button_pressed2(X11 app, Matrix *matrix, int offset);

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

            redraw(app);
            int offset = 100;

            if (text[0] == '1' || matrix.val == NULL)
                handle_button_pressed1(&matrix);
            else if (text[0] == '2')
                handle_button_pressed2(app, &matrix, offset);

            int is_directed = text[0] == 'u' ? 0 : 1;
            draw_graph(app, matrix, is_directed, offset, offset);
        }
    }

    close_window(app);
    free_matrix(&matrix);
    printf("Bye!");
    return 0;
}

void handle_button_pressed1(Matrix *matrix) {
    printf("\nGenerating matrix 1...\n");
    free_matrix(matrix);
    matrix->val = get_boolean_matrix(10 + n3, 1.0 - n3 * 0.01 - n4 * 0.005 - 0.15).val;
    matrix->n = 10 + n3;
    print_matrix(*matrix, 1);
    dfs(*matrix);
    bfs(*matrix);
}

void handle_button_pressed2(X11 app, Matrix *matrix, int offset) {
}
