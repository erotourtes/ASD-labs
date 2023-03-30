// You need to install X11 library (sudo dnf install libX11-devel)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "./App.c"

void draw_graph(X11 app);


typedef struct {
    int x;
    int y;
} Point;

Point* get_coordinates(int n);

int main() {
    X11 app = init("Lab #3");

    XEvent event;
    KeySym key;
    char text[255];

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
                draw_graph(app);
            }
        }
    }

    close_window(app);
    return 0;
}

Point* get_coordinates(int n) {
    Point *points = malloc(n * sizeof(Point));
    int distance = 100;

    int k = n - 1; // number of points without center
    int num_in_row = floor((k + 4) / 4);
    int rest = k - (num_in_row * 4 - 4);
    int cur = 0;

    int x = -distance;
    int y = 0;

    // Center
    points[n - 1].x = ((num_in_row - 1) * distance + (rest > 1 ? distance : 0)) / 2;
    points[n - 1].y = ((num_in_row - 1) * distance) / 2;

    // Top row;
    int cur_distance = distance;
    if (rest == 1) {
        cur_distance = distance * (num_in_row - 1) / (num_in_row);
        x = -cur_distance;
    }

    for (int i = 0; i < num_in_row; i++) {
        x += cur_distance;
        points[cur++] = (Point) {x, y};
    }

    if (rest > 0) {
        x += cur_distance;
        points[cur++] = (Point) {x, y};
        rest--;
    }

    // Right column
    cur_distance = distance;
    if (rest == 2) {
        cur_distance = distance * (num_in_row - 1) / (num_in_row);
    }
    for (int i = 0; i < num_in_row - 1; i++) {
        y += cur_distance;
        points[cur++] = (Point) {x, y};
    }

    if (rest == 2) {
        y += cur_distance;
        points[cur++] = (Point) {x, y};
        rest--;
    }

    // Bottom row
    for (int i = 0; i < num_in_row - 1; i++) {
        x -= distance;
        points[cur++] = (Point) {x, y};
    }

    if (rest == 1) {
        x -= distance;
        points[cur++] = (Point) {x, y};
        rest--;
    }

    // Left column
    for (int i = 0; i < num_in_row - 2; i++) {
        y -= distance;
        points[cur++] = (Point) {x, y};
    }

    return points;
}

void draw_graph(X11 app) {
    // 10
    int n = 14;
    Point *points = get_coordinates(n);

    int circle_radius = 20;
    int offset = 100;
    int ch_x_offset = 3;
    int ch_y_offset = 5;
    int distance = 100;

    unsigned long blue = 0x3200FF;
    unsigned long dark = 0x141405;

    for (int i = 0; i < n; i++) {
        XSetForeground(app.dis, app.gc, blue);

        XFillArc(app.dis, app.win, app.gc, points[i].x - circle_radius + offset, points[i].y - circle_radius + offset, circle_radius * 2, circle_radius * 2, 0, 360 * 64);

//        XSetForeground(app.dis, app.gc, dark);
//        char name = (char)graph[current++];
//        XDrawString(app.dis, app.win, app.gc, 100 * i - ch_x_offset, 100 + ch_y_offset, &name, 1);
    }

    free(points);

    // to bottom
//    for (int i = 1; i <= num_in_row; i++) {
//        XFillArc(app.dis, app.win, app.gc, 100 * (num_in_row + rest + 1) - circle_radius, 100 * i - circle_radius, circle_radius * 2, circle_radius * 2, 0, 360 * 64);
//    }

    // to left
    // to top

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