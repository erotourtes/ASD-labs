// You need to install X11 library (sudo dnf install libX11-devel)

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define width 300
#define height 300

Display *dis;
int screen;
Window win;
GC gc;

char ProgName[] = "Lab #3";

void init_x();

void close_x();

void redraw();

void arrow(float fi, int px, int py);

void draw_graph();

int main() {
    XEvent event;
    KeySym key;
    char text[255];

    init_x();

    while (1) {
        XNextEvent(dis, &event);
        // Expose event
        if (event.type == Expose && event.xexpose.count == 0) {
            redraw();
        }
        // KeyPress event
        if (event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1) {
            if (text[0] == 'q') {
                close_x();
            } else {
                draw_graph();
            }
        }
    }

    printf("Hello WORLD!\n");
    return 0;
}

void init_x() {
    unsigned long black, white;
    dis = XOpenDisplay((char *) 0);
    screen = DefaultScreen(dis);

    black = BlackPixel(dis, screen);
    white = WhitePixel(dis, screen);

    win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0, width, height, 5, black, white);


    XSetStandardProperties(dis, win, ProgName, ProgName, None, NULL, 0, NULL);

    XSelectInput(dis, win, ExposureMask | KeyPressMask);

    gc = XCreateGC(dis, win, 0, 0);

    XMapRaised(dis, win);
}

void close_x() {
    XFreeGC(dis, gc);
    XDestroyWindow(dis, win);
    XCloseDisplay(dis);
    exit(0);
}

void redraw() {
    XClearWindow(dis, win);
};

void draw_graph() {
    char *nn[3] = {"1", "2", "3"};
    int nx[3] = {100, 200, 300};
    int ny[3] = {100, 200, 300};
    int dx = 16, dy = 16, dtx = 5;
    int i;

    unsigned long bpen = 0x3200FF;
    unsigned long fpen = 0x141405;

    XSetForeground(dis, gc, bpen);

    XDrawLine(dis, win, gc, nx[0], ny[0], nx[1], ny[1]);
    arrow(0, nx[1], ny[1]);
    XDrawArc(dis, win, gc, nx[0], ny[0] - 40, nx[2] - nx[0], 80, 0, 180*64);
    arrow( -45.0, nx[2] - dx * 0.5, ny[2] - dy * 0.8);

    XSetForeground(dis, gc, fpen);

    for(i = 0; i <= 2; i++) {
        XFillArc(dis, win, gc, nx[i] - dx, ny[i] - dy, dx * 2, dy * 2, 0, 360 * 64);
    }

    XSetForeground(dis, gc, bpen);
    XSetLineAttributes(dis, gc, 2, LineSolid, CapButt, JoinMiter);

    for(i = 0 ; i <= 2; i++) {
        XDrawString(dis, win, gc, nx[i] - dtx, ny[i] + dy, nn[i], 1);
    }
}

void arrow(float fi, int px, int py) {
    fi = 3.1415926 * (180.0 - fi) / 180.0;
    int lx, ly, rx, ry;

    lx = px + 15 * cos(fi + 0.3);
    rx = px + 15 * cos(fi - 0.3);
    ly = py + 15 * sin(fi + 0.3);
    ry = py + 15 * sin(fi - 0.3);
    XDrawLine(dis, win, gc, lx, ly, px, py);
    XDrawLine(dis, win, gc, rx, ry, px, py);
}