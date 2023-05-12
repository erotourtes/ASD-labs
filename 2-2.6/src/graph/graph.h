//
// Created by sirmax on 5/9/23.
//

#include "../matrix/matrix.h"
#include "../Utils/list.h"

#ifndef INC_2_2_5_GRAPH_H
#define INC_2_2_5_GRAPH_H

typedef struct {
    List *edges;
    int value;
} GraphNode;

typedef struct {
    int weight;
    GraphNode *from;
    GraphNode *to;
} GraphEdge;

typedef struct {
    List *nodes;
    int size;
} Graph;

Graph get_graph_from(Matrix m, Matrix weights);

void free_graph(Graph *g);

GraphNode *graph_add_node(Graph *g, int value, List *edges);

Graph init_graph();

GraphNode *graph_get_node(Graph g, int value);

void graph_create_edge(Graph *g, GraphNode *from, GraphNode *to, int weight);

#endif //INC_2_2_5_GRAPH_H
