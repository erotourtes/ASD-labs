#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "X11.h"

#define width 650
#define height 500

X11 init(char *prog_name);

void close_window(X11 app);

void redraw(X11 app);

X11 init(char *prog_name) {
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
}