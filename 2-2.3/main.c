// You need to install X11 library (sudo dnf install libX11-devel)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./Point.h"
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
        XDrawString(app.dis, app.win, app.gc, points[i].x - ch_x_offset, points[i].y + ch_y_offset, name,
                    (i < 9 ? 1 : 2));
    }
}

void draw_loop(X11 app, int circle_radius, int x, int y) {
    int arc_width = circle_radius * 2;
    int arc_height = circle_radius * 1.5;
    XDrawArc(app.dis, app.win, app.gc, x, y, arc_width, arc_height, 0 * 64,
             360 * 64);
}

int in_range(int x, int a, int b) {
    return a < x && x < b || b < x && x < a;
}

int is_overlapping(Point *points, int n, int i, int j) {
    Point p1 = points[i];
    Point p2 = points[j];

    // overlapping with center node
    Point center = points[n - 1];
    if ((p1.x + p2.x) / 2 == center.x && (p1.y + p2.y) / 2 == center.y)
        return 1;

    for (int k = 0; k < n; k++) {
        if (k == i || k == j) continue;
        Point cur = points[k];

        int is_in_row = p1.y == p2.y && p1.y == cur.y && in_range(cur.x, p1.x, p2.x);
        int is_in_column = p1.x == p2.x && p1.x == cur.x && in_range(cur.y, p1.y, p2.y);
        if (is_in_row || is_in_column)
            return 1;
    }

    return 0;
}

void draw_graph(X11 app, Matrix matrix) {
    Point *points = get_coordinates(matrix.n, 100);
    int offset = 100;
    applyOffset(points, matrix.n, offset);

    int circle_radius = 20;
    unsigned long blue = 0x83c9f4;
    unsigned long dark = 0x2b061e;

    XSetLineAttributes(app.dis, app.gc, 2, LineSolid, CapButt, JoinMiter);

    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.n; j++) {
//            if (matrix.val[i][j] == 0) continue;

//            if (i == 2 && j == 8) {
//            if (i == 9 && j == 0) {
            if (1) {
                if (is_overlapping(points, matrix.n, i, j))
                    XSetLineAttributes(app.dis, app.gc, 4, LineOnOffDash, CapButt, JoinMiter);

                draw_arrow_line(app, points[i], points[j], circle_radius);

                XDrawLine(app.dis, app.win, app.gc, points[i].x, points[i].y, points[j].x, points[j].y);
                XSetLineAttributes(app.dis, app.gc, 2, LineSolid, CapButt, JoinMiter);
            }
        }
    }

//    draw_nodes_names(app, points, matrix.n, circle_radius, blue, dark);

    free(points);
}