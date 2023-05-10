//
// Created by sirmax on 4/27/23.
//

#include "../matrix/matrix.h"
#include "../app/app.h"
#include "Point.h"

#ifndef INC_2_2_5_DRAW_GRAPH_H
#define INC_2_2_5_DRAW_GRAPH_H

void draw_graph(X11 app, Matrix matrix, Matrix weights, Point *points, int is_directed, int circle_radius);

void highlight_edge_between(X11 app, Matrix matrix, Point* coordinates, int from_node, int to_node, int circle_radius);

#endif //INC_2_2_5_DRAW_GRAPH_H
