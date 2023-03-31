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
    matrix.val[0][3] = 1;
    matrix.val[6][7] = 1;
    matrix.val[10][0] = 1;
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

void applyOffset(Point *points, int n, int offset) {
    for (int i = 0; i < n; i++) {
        points[i].x += offset;
        points[i].y += offset;
    }
}

void draw_nodes_names(X11 app, Point *points, int len, int circle_radius, unsigned long bg, unsigned long fg) {
    int ch_x_offset = 3;
    int ch_y_offset = 5;

    for (int i = 0; i < len; i++) {
        XSetForeground(app.dis, app.gc, bg);

        XFillArc(app.dis, app.win, app.gc, points[i].x - circle_radius, points[i].y - circle_radius,
                 circle_radius * 2, circle_radius * 2, 0, 360 * 64);

        XSetForeground(app.dis, app.gc, fg);
        char name[2];
        sprintf(name, "%d", i + 1);
        XDrawString(app.dis, app.win, app.gc, points[i].x - ch_x_offset, points[i].y + ch_y_offset, &name,
                    (i < 9 ? 1 : 2));
    }
}

void draw_loop(X11 app, int circle_radius, int x, int y) {
    int arc_width = circle_radius * 2;
    int arc_height = circle_radius * 1.5;
    XDrawArc(app.dis, app.win, app.gc, x, y, arc_width, arc_height, 0 * 64,
             360 * 64);
}

int min(int a, int b) {
    return a < b ? a : b;
}

void draw_arc_ver(X11 app, Point *p1, Point *p2, int angle) {
    int arc_width = abs(p1->x - p2->x);
    int arc_height = arc_width * 0.3;
    int arc_top_left_x = min(p1->x, p2->x);
    int arc_top_left_y = p1->y - arc_height * 0.5; // arc function is not drawing full arc
    XDrawArc(app.dis, app.win, app.gc, arc_top_left_x, arc_top_left_y, arc_width, arc_height, 0 * 64,
             angle * 64);
}

void draw_arc_hor(X11 app, Point *p1, Point *p2, int angle) {
    int arc_height = abs(p1->y - p2->y);
    int arc_width = arc_height * 0.3;
    int arc_top_left_x = p1->x - arc_width * 0.5;
    int arc_top_left_y = min(p1->y, p2->y);
    XDrawArc(app.dis, app.win, app.gc, arc_top_left_x, arc_top_left_y, arc_width, arc_height, 90 * 64,
             angle * 64);
}

void draw_graph(X11 app, Matrix matrix) {
    Point *points = get_coordinates(matrix.n, 100);
    int offset = 100;
    applyOffset(points, matrix.n, offset);

    int circle_radius = 20;
    unsigned long blue = 0x3200FF;
    unsigned long dark = 0x141405;

    XSetLineAttributes(app.dis, app.gc, 2, LineSolid, CapButt, JoinMiter);


    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.n; j++) {
            if (matrix.val[i][j] == 0) continue;

            if (i == j) {
                draw_loop(app, circle_radius, points[i].x, points[i].y);
            } else if (points[i].y == points[j].y) {
                int angle = points[i].y == offset ? 180 : -180;
                draw_arc_ver(app, &points[i], &points[j], angle);
            } else if (points[i].x == points[j].x) {
                int angle = points[i].x == offset ? 180 : -180;
                draw_arc_hor(app, &points[i], &points[j], angle);
            } else {
                XDrawLine(app.dis, app.win, app.gc, points[i].x, points[i].y, points[j].x, points[j].y);
            }
        }
    }

    draw_nodes_names(app, points, matrix.n, circle_radius, blue, dark);

    free(points);
}