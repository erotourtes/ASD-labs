// You need to install X11 library (sudo dnf install libX11-devel)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./app.c"
#include "./matrix.c"
#include "./graph_coords.c"

void draw_graph(X11 app, Matrix matrix);

int main() {
    X11 app = init("Lab #3");

    XEvent event;
    KeySym key;
    char text[255];

    Matrix matrix = get_boolean_matrix();

    short running = 1;
    while (running) {
        XNextEvent(app.dis, &event);
        // Expose event
        if (event.type == Expose && event.xexpose.count == 0) {
            redraw(app);
        }
        // KeyPress event
        if (event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
            if (text[0] == 'q') {
                running = 0;
            } else {
                draw_graph(app, matrix);
            }
        }
    }

    close_window(app);
    free_matrix(matrix);
    printf("Bye!");
    return 0;
}


void draw_graph(X11 app, Matrix matrix) {
    Point *points = get_coordinates(matrix.n, 100);

    int circle_radius = 20;
    int offset = 100;
    int ch_x_offset = 3;
    int ch_y_offset = 5;
    int distance = 100;

    unsigned long blue = 0x3200FF;
    unsigned long dark = 0x141405;

    for (int i = 0; i < matrix.n; i++) {
        XSetForeground(app.dis, app.gc, blue);

        XFillArc(app.dis, app.win, app.gc, points[i].x - circle_radius + offset, points[i].y - circle_radius + offset,
                 circle_radius * 2, circle_radius * 2, 0, 360 * 64);

        XSetForeground(app.dis, app.gc, dark);
        char name[2];
        sprintf(name, "%d", i + 1);
        XDrawString(app.dis, app.win, app.gc, points[i].x - ch_x_offset + offset, points[i].y + ch_y_offset + offset, &name, (i < 9 ? 1 : 2));
    }

    free(points);

//    XDrawLine(app.dis, app.win, app.gc, 0, 0, 100, 100);
//    XDrawLine(app.dis, app.win, app.gc, nx[0], ny[0], nx[1], ny[1]);
//    draw_arrow(0, nx[1], ny[1], app);
//    XDrawArc(app.dis, app.win, app.gc, nx[0], ny[0] - 40, nx[2] - nx[0], 80, 0, 180 * 64);
//    draw_arrow(-45.0, nx[2] - dx * 0.5, ny[2] - dy * 0.8, app);
//
//    XSetForeground(app.dis, app.gc, fpen);
//
//    for (i = 0; i <= 2; i++) {
//        XFillArc(app.dis, app.win, app.gc, nx[i] - dx, ny[i] - dy, dx * 2, dy * 2, 0, 360 * 64);
//    }
//
//    XSetForeground(app.dis, app.gc, blue);
//    XSetLineAttributes(app.dis, app.gc, 2, LineSolid, CapButt, JoinMiter);
//
//    for (i = 0; i <= 2; i++) {
//        XDrawString(app.dis, app.win, app.gc, nx[i] - dtx, ny[i] + dy, nn[i], 1);
//    }
}