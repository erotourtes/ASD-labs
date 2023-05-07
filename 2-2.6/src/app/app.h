//
// Created by sirmax on 4/27/23.
//

#include <X11/Xlib.h>

#ifndef INC_2_2_5_APP_H
#define INC_2_2_5_APP_H

typedef struct {
    Display *dis;
    int screen;
    Window win;
    GC gc;
} X11;


X11 init(char *prog_name);

void close_window(X11 app);

void redraw(X11 app);

#endif //INC_2_2_5_APP_H