#ifndef X11_H

typedef struct {
    Display *dis;
    int screen;
    Window win;
    GC gc;
} X11;

#define X11_H

#endif
