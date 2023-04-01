// You need to install X11 library (sudo dnf install libX11-devel)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./Point.c"
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

void draw_arc_hor(X11 app, Point *p1, Point *p2, int angle, int start_angle) {
    int arc_height = abs(p1->y - p2->y);
    int arc_width = arc_height * 0.3;
    int arc_top_left_x = p1->x - arc_width * 0.5;
    int arc_top_left_y = min(p1->y, p2->y);
    XDrawArc(app.dis, app.win, app.gc, arc_top_left_x, arc_top_left_y, arc_width, arc_height, start_angle * 64,
             angle * 64);
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
            if (1) {
                if (is_overlapping(points, matrix.n, i, j))
                    XSetLineAttributes(app.dis, app.gc, 4, LineOnOffDash, CapButt, JoinMiter);

                if (points[i].x < points[j].x || points[i].y < points[j].y) {
                    XDrawLine(app.dis, app.win, app.gc, points[i].x, points[i].y, points[j].x, points[j].y);
                    double dy = (points[j].y - points[i].y);
                    double dx = (points[j].x - points[i].x);
                    double angle = atan(dy / dx);
                    Point p = {points[j].x - circle_radius * cos(angle), points[j].y - circle_radius * sin(angle)};
                    draw_head_arrow(app, p, -angle * 180 / M_PI);
                } else {
                    XDrawLine(app.dis, app.win, app.gc, points[i].x, points[i].y, points[j].x, points[j].y);
                    double dy = (points[j].y - points[i].y);
                    double dx = (points[j].x - points[i].x);
                    double angle = atan(dy / dx);
                    Point p = {points[j].x + circle_radius * cos(angle), points[j].y + circle_radius * sin(angle)};
                    draw_head_arrow(app, p, 180 - angle * 180 / M_PI);
                }

                XSetLineAttributes(app.dis, app.gc, 2, LineSolid, CapButt, JoinMiter);
            }
        }
    }

    draw_nodes_names(app, points, matrix.n, circle_radius, blue, dark);

    free(points);
}

void draw_graph1(X11 app, Matrix matrix) {
    Point *points = get_coordinates(matrix.n, 100);
    int offset = 100;
    applyOffset(points, matrix.n, offset);

    int circle_radius = 20;
    unsigned long blue = 0x83c9f4;
    unsigned long dark = 0x2b061e;

    XSetLineAttributes(app.dis, app.gc, 2, LineSolid, CapButt, JoinMiter);

    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.n; j++) {
            if (i == 9 && j == 0) {

                XDrawLine(app.dis, app.win, app.gc, points[i].x, points[i].y, points[j].x, points[j].y);
                double dy = points[j].y - points[i].y;
                double dx = points[j].x - points[i].x;
                double angle = atan(dy / dx);
                Point p = {points[j].x + circle_radius * cos(angle), points[j].y + circle_radius * sin(angle)};
                draw_head_arrow(app, p, angle * 180 / M_PI);
            }
            if (matrix.val[i][j] == 0) continue;


            if (i == j) {
//                draw_loop(app, circle_radius, points[i].x, points[i].y);
            } else if (points[i].y == points[j].y) {
//                int angle = points[i].y == offset ? 180 : -180;
//                draw_arc_ver(app, &points[i], &points[j], angle);
            } else if (points[i].x == points[j].x) {
//                int angle = points[i].x == offset ? 180 : -180;
//                draw_arc_hor(app, &points[i], &points[j], angle, 90);
            } else {
                if (i == 7 && j == 2) {
//                    draw_arc(app.dis, app.win, app.gc, points[i].x, points[i].y, points[j].x, points[j].y, 100);
//                    draw_arc(app, points[i], points[j], 100);

//                    int x_center = points[i].x;
//                    int y_center = points[j].y;
//                    int dx = abs(points[i].x - points[j].x);
//                    int dy = abs(points[j].y - points[i].y);
//                    int radius = sqrt(dx*dx + dy*dy) / 2;
//                    int start_angle = atan2(points[i].y - points[j].y, points[i].x - points[j].x) * 180 / M_PI;
//                    int end_angle = atan2(points[j].y - y_center, points[j].x - x_center) * 180 / M_PI;
//                    XDrawArc(app.dis, app.win, app.gc, x_center - radius, y_center - radius, radius*2, radius*2, start_angle*64, (end_angle - start_angle)*64);
                } else {
                    if (points[i].x < points[j].x) {
                        XDrawLine(app.dis, app.win, app.gc, points[i].x, points[i].y, points[j].x, points[j].y);
                        double dy = points[j].y - points[i].y;
                        double dx = points[j].x - points[i].x;
                        double angle = atan(dy / dx);
                        Point p = {points[j].x - circle_radius * cos(angle), points[j].y - circle_radius * sin(angle)};
                        draw_head_arrow(app, p, -angle * 180 / M_PI);
                    } else {
                        XDrawLine(app.dis, app.win, app.gc, points[i].x, points[i].y, points[j].x, points[j].y);
                        double dy = points[j].y - points[i].y;
                        double dx = points[j].x - points[i].x;
                        double angle = atan(dy / dx);
                        Point p = {points[j].x + circle_radius * cos(angle), points[j].y + circle_radius * sin(angle)};
                        draw_head_arrow(app, p, 180 - angle * 180 / M_PI);
                    }
                }
            }
        }
    }

    draw_nodes_names(app, points, matrix.n, circle_radius, blue, dark);

    free(points);
}