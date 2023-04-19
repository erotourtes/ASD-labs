#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <limits.h>

#include "Point.h"
#include "Matrix.h"
#include "graph_coords.c"

void applyOffset(Point *points, int n, int offsetX, int offsetY) {
    for (int i = 0; i < n; i++) {
        points[i].x += offsetX;
        points[i].y += offsetY;
    }
}

void draw_nodes(X11 app, Point *points, int len, int circle_radius) {
    int ch_x_offset = 3;
    int ch_y_offset = 5;

    unsigned long bg = 0x83c9f4;
    unsigned long fg = 0x2b061e;

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

int is_through_center(Point *p, int i, int j, int n) {
    Point p1 = p[i];
    Point p2 = p[j];
    Point center = p[n - 1];
    return (p1.x + p2.x) / 2 == center.x && (p1.y + p2.y) / 2 == center.y;
}

int in_range(int x, int a, int b) {
    return a < x && x < b || b < x && x < a;
}

int is_overlapping(Point *points, int n, int i, int j) {
    Point p1 = points[i];
    Point p2 = points[j];

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

int is_arrows_overlaps(Matrix matrix, int i, int j) {
    int **m = matrix.val;

    return m[i][j] && m[j][i];
}

void draw_head_arrow(X11 app, Point p, double deg) {
    double fi = M_PI / 180.0 * (180.0 - deg);
    float arrow_angle = 0.3f;
    int len = 15;

    int lx = p.x + len * cos(fi + arrow_angle);
    int rx = p.x + len * cos(fi - arrow_angle);
    int ly = p.y + len * sin(fi + arrow_angle);
    int ry = p.y + len * sin(fi - arrow_angle);

    XDrawLine(app.dis, app.win, app.gc, lx, ly, p.x, p.y);
    XDrawLine(app.dis, app.win, app.gc, rx, ry, p.x, p.y);
}

void draw_loop(X11 app, double circle_radius, Point p, int is_directed) {
    int arc_width = floor(circle_radius * 1.5);
    int arc_height = floor(circle_radius * 1.5);
    XDrawArc(app.dis, app.win, app.gc, p.x - circle_radius - arc_width / 2.0, p.y - arc_height, arc_width, arc_height,
             0 * 64,
             360 * 64);

    Point arrow_point = {p.x - circle_radius, p.y};
    if (is_directed)
        draw_head_arrow(app, arrow_point, -15);
}

void draw_line(X11 app, Point p1, Point p2) {
    XDrawLine(app.dis, app.win, app.gc, p1.x, p1.y, p2.x, p2.y);
}

void draw_arrow_line(X11 app, Point p1, Point p2, double circle_radius) {
    double dy = -(p2.y - p1.y);
    double dx = (p2.x - p1.x);
    double angle = atan(dy / dx);

    int to_left = p1.x > p2.x; // to left (left top; left bottom)
    if (to_left) {
        Point p = {p2.x + circle_radius * cos(angle), p2.y - circle_radius * sin(angle)};
        draw_head_arrow(app, p, 180.0 + angle * 180.0 / M_PI);
    } else { // to right (right top; right bottom) && top && bottom
        Point p = {p2.x - circle_radius * cos(angle), p2.y + circle_radius * sin(angle)};
        draw_head_arrow(app, p, angle * 180 / M_PI);
    }

    draw_line(app, p1, p2);
}

void draw_through_angle(X11 app, Point *points, int i, int j, int circle_radius, int is_directed, int is_small) {
    Point p1 = points[i];
    Point p2 = points[j];

    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    // flip in opposite direction
    int to_opposite = is_directed == 1 ? -1 : 1;

    double offsetX = 2 * circle_radius + log10(abs(dy));
    double offsetY = 2 * circle_radius + log10(abs(dx));

    int rand_offset = rand() % circle_radius * to_opposite;

    if (points[i].x > points[j].x && points[i].y > points[j].y) {
        offsetY = -1 * offsetY + rand_offset;
    } else if (points[i].x < points[j].x && points[i].y > points[j].y) {
        offsetY = to_opposite * offsetY + rand_offset;
        offsetX = to_opposite * offsetX;
    } else if (points[i].x < points[j].x && points[i].y < points[j].y) {
        offsetX = to_opposite * offsetX + rand_offset;
        offsetY = (to_opposite == -1 ? 1 : -1) * offsetY;
    }

    if (dx == 0) {
        offsetY = 0;
        if (points[i].y > points[j].y)
            offsetX *= to_opposite;
    }
    if (dy == 0) {
        offsetX = 0;
        if (points[i].x > points[j].x)
            offsetY *= to_opposite;
    }

    if (is_small) {
        offsetX /= 5;
        offsetY /= 5;
    }

    Point middle = (Point) {(p1.x + p2.x) / 2 - offsetX, (p1.y + p2.y) / 2 - offsetY};

    draw_line(app, points[i], middle);
    if (is_directed)
        draw_arrow_line(app, middle, points[j], circle_radius);
    else
        draw_line(app, middle, points[j]);
}

void draw_graph(X11 app, Matrix matrix, int is_directed, int offsetX, int offsetY) {
    Point *points = get_coordinates(matrix.n, 150);
    applyOffset(points, matrix.n, offsetX, offsetY);

    int circle_radius = 20;

    XSetLineAttributes(app.dis, app.gc, 2, LineSolid, CapButt, JoinMiter);

    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.n; j++) {
            if (matrix.val[i][j] == 0) continue;

            XSetForeground(app.dis, app.gc, rand() % USHRT_MAX);

            if (i == j)
                draw_loop(app, circle_radius, (Point) {points[i].x, points[i].y}, is_directed);
            else if (is_through_center(points, i, j, matrix.n) || is_overlapping(points, matrix.n, i, j))
                draw_through_angle(app, points, i, j, circle_radius, is_directed, 0);
            else if (is_directed && is_arrows_overlaps(matrix, i, j))
                draw_through_angle(app, points, i, j, circle_radius, is_directed, 1);
            else {
                if (is_directed)
                    draw_arrow_line(app, points[i], points[j], circle_radius);
                else
                    draw_line(app, points[i], points[j]);
            }
        }
    }

    draw_nodes(app, points, matrix.n, circle_radius);

    free(points);
}