#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define width 500
#define height 400

typedef struct {
    Display *dis;
    int screen;
    Window win;
    GC gc;
} X11;

X11 init(char *prog_name);

void close_window(X11 app);

void redraw(X11 app);

X11 init(char* prog_name) {
    Display *dis = XOpenDisplay((char *) 0);
    int screen = DefaultScreen(dis);
    Window win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0, width, height, 5, 0, WhitePixel(dis, screen));
    GC gc = XCreateGC(dis, win, 0, 0);

    XSetStandardProperties(dis, win, prog_name, prog_name, None, NULL, 0, NULL);
    XSelectInput(dis, win, ExposureMask | KeyPressMask);

    XMapRaised(dis, win);

    return (X11) {dis, screen, win, gc};
}


void close_window(X11 app) {
    XFreeGC(app.dis, app.gc);
    XDestroyWindow(app.dis, app.win);
    XCloseDisplay(app.dis);
}

void redraw(X11 app) {
    XClearWindow(app.dis, app.win);
};

void draw_arrow(float grad, int x, int y, X11 app) {
    float fi = M_PI / 180.0 * (180.0 - grad) ;
    float arrow_angle = 0.3;
    int len = 15;

    int lx = x + len * cos(fi + arrow_angle);
    int rx = x + len * cos(fi - arrow_angle);
    int ly = y + len * sin(fi + arrow_angle);
    int ry = y + len * sin(fi - arrow_angle);

    XDrawLine(app.dis, app.win, app.gc, lx, ly, x, y);
    XDrawLine(app.dis, app.win, app.gc, rx, ry, x, y);
}
