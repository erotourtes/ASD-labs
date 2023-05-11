//
// Created by sirmax on 4/27/23.
//

#include "../matrix/matrix.h"
#include "../app/app.h"
#include "Point.h"
#include "../graph/graph.h"

#ifndef INC_2_2_5_DRAW_GRAPH_H
#define INC_2_2_5_DRAW_GRAPH_H

void draw_graph(X11 app, Matrix matrix, Matrix weights, Point *points, int is_directed, int circle_radius);

void draw_graph_edge(X11 app, Matrix m, Point *points, GraphEdge edge, int circle_radius);

void draw_weight_count(X11 app, int minimal_weight);

#endif //INC_2_2_5_DRAW_GRAPH_H
