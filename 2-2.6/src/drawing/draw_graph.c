#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "../matrix/matrix.h"
#include "draw_graph.h"
#include "graph_coords.h"
#include "../Utils/list.h"

typedef unsigned long u64;

void draw_node(X11 app, Point point, int number, int circle_radius, u64 bg, u64 fg) {
    int ch_x_offset = 3;
    int ch_y_offset = 5;

    XSetForeground(app.dis, app.gc, bg);

    XFillArc(app.dis, app.win, app.gc, point.x - circle_radius, point.y - circle_radius,
             circle_radius * 2, circle_radius * 2, 0, 360 * 64);

    XSetForeground(app.dis, app.gc, fg);
    char name[2];
    sprintf(name, "%d", number);
    XDrawString(app.dis, app.win, app.gc, point.x - ch_x_offset, point.y + ch_y_offset, name,
                (number < 9 ? 1 : 2));

}

void print_weight(X11 app, Point p, int number) {
    char text[4];
    sprintf(text, "%d", number);

    // drawing square to better see the text
    XSetBackground(app.dis, app.gc, 0xFFFFFF);
    XSetForeground(app.dis, app.gc, 0xFFFFFF);
    XFillRectangle(app.dis, app.win, app.gc, p.x, p.y - 10, 12, 12);

    // drawing text
    XSetForeground(app.dis, app.gc, 0xFF0000);
    XDrawString(app.dis, app.win, app.gc, p.x, p.y, text, number == 0 ? 1 : (int) (log10(number) + 1));
}


void draw_nodes(X11 app, Point *points, int len, int circle_radius, unsigned long bg, unsigned long fg) {
    for (int i = 0; i < len; i++) {
        draw_node(app, points[i], i + 1, circle_radius, bg, fg);
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

void draw_loop(X11 app, double circle_radius, int weight, Point p, int is_directed) {
    int arc_width = floor(circle_radius * 1.5);
    int arc_height = floor(circle_radius * 1.5);
    XDrawArc(app.dis, app.win, app.gc, p.x - circle_radius - arc_width / 2.0, p.y - arc_height, arc_width, arc_height,
             0 * 64,
             360 * 64);

    Point arrow_point = {p.x - circle_radius, p.y};
    if (is_directed)
        draw_head_arrow(app, arrow_point, -15);

    print_weight(app, (Point){ p.x - arc_width / 2, p.y - arc_height / 2 }, weight);
}

void draw_line(X11 app, Point p1, Point p2, int weight) {
    XDrawLine(app.dis, app.win, app.gc, p1.x, p1.y, p2.x, p2.y);
    if (weight != -1) {
        Point p = (Point) {(p1.x + p2.x) / 2, (p1.y + p2.y) / 2};
        print_weight(app, p, weight);
    }
}

void draw_arrow_line(X11 app, Point p1, Point p2, double circle_radius, int weight) {
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

    return draw_line(app, p1, p2, weight);
}

void
draw_through_angle(X11 app, Point *points, int i, int j, int weight, int circle_radius, int is_directed, int is_small) {
    Point p1 = points[i];
    Point p2 = points[j];

    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    // flip in opposite direction
    int to_opposite = is_directed == 1 ? -1 : 1;

    double offsetX = 2 * circle_radius + log10(abs(dy));
    double offsetY = 2 * circle_radius + log10(abs(dx));

    if (points[i].x > points[j].x && points[i].y > points[j].y) {
        offsetY = -1 * offsetY;
    } else if (points[i].x < points[j].x && points[i].y > points[j].y) {
        offsetY = to_opposite * offsetY;
        offsetX = to_opposite * offsetX;
    } else if (points[i].x < points[j].x && points[i].y < points[j].y) {
        offsetX = to_opposite * offsetX;
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

    draw_line(app, points[i], middle, -1);
    if (is_directed)
        draw_arrow_line(app, middle, points[j], circle_radius, -1);
    else
        draw_line(app, middle, points[j], -1);

    print_weight(app, middle, weight);
}

void
draw_right_line(X11 app, Matrix matrix, Point *points, int i, int j, int weight, int circle_radius, int is_directed) {
    if (i == j)
        draw_loop(app, circle_radius, weight, (Point) {points[i].x, points[i].y}, is_directed);
    else if (is_through_center(points, i, j, matrix.n) || is_overlapping(points, matrix.n, i, j))
        draw_through_angle(app, points, i, j, weight, circle_radius, is_directed, 0);
    else if (is_directed && is_arrows_overlaps(matrix, i, j))
        draw_through_angle(app, points, i, j, weight, circle_radius, is_directed, 1);
    else {
        if (is_directed)
            draw_arrow_line(app, points[i], points[j], circle_radius, weight);
        else
            draw_line(app, points[i], points[j], weight);
    }
}

void draw_graph(X11 app, Matrix matrix, Matrix weights, Point *points, int is_directed, int circle_radius) {
    XSetLineAttributes(app.dis, app.gc, 2, LineSolid, CapButt, JoinMiter);

    for (int i = 0; i < matrix.n; i++) {
        for (int j = 0; j < matrix.n; j++) {
            if (matrix.val[i][j] == 0) continue;
            int weight = weights.val[i][j];
            draw_right_line(app, matrix, points, i, j, weight, circle_radius, is_directed);
            XSetForeground(app.dis, app.gc, rand() % USHRT_MAX);
        }
    }

    unsigned long bg = 0x83c9f4;
    unsigned long fg = 0x2b061e;
    draw_nodes(app, points, matrix.n, circle_radius, bg, fg);
}

void highlight_edge_between(X11 app, Matrix m, Point *points, int from_node, int to_node, int circle_radius) {
    unsigned long current_color = 0xF3DE8A;
    unsigned long next_color = 0xEB9486;
    unsigned long visited_color = 0x9381FF;
    unsigned long fg = 0x2b061e;
    unsigned long arrow_color = 0x312A58;

    XSetLineAttributes(app.dis, app.gc, 7, LineSolid, CapButt, JoinMiter);
    XSetForeground(app.dis, app.gc, current_color);

    Point from_point = points[from_node];
    Point to_point = points[to_node];

    int is_all_visited = from_node == to_node;
    if (is_all_visited) {
        draw_node(app, from_point, from_node + 1, circle_radius, visited_color, fg);
    } else {
        XSetForeground(app.dis, app.gc, arrow_color);
        draw_right_line(app, m, points, from_node, to_node, 0, circle_radius, 1);
        draw_node(app, from_point, from_node + 1, circle_radius, current_color, fg);
        draw_node(app, to_point, to_node + 1, circle_radius, next_color, fg);
    }

    XSetLineAttributes(app.dis, app.gc, 2, LineSolid, CapButt, JoinMiter);
    XSetForeground(app.dis, app.gc, 0x000000);
}