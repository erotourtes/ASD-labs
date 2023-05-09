//
// Created by sirmax on 5/9/23.
//

#include "../matrix/matrix.h"
#include "../Utils/list.h"

#ifndef INC_2_2_5_GRAPH_H
#define INC_2_2_5_GRAPH_H

typedef struct {
    int weight;
    int from;
    int to;
} GraphEdge;

typedef struct {
    List *edges;
    int value;
} GraphNode;

typedef struct {
    List *nodes;
    int size;
} Graph;

#endif //INC_2_2_5_GRAPH_H
