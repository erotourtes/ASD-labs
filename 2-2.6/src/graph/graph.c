//
// Created by sirmax on 5/9/23.
//

#include "graph.h"
#include <stdlib.h>

Graph init_graph() {
    Graph g = {list_init(), 0};
    return g;
}

GraphNode *graph_create_node(int value, List *edges) {
    GraphNode *node = (GraphNode *) malloc(sizeof(GraphNode));
    node->value = value;
    node->edges = edges;
    return node;
}

void graph_add_node(Graph *g, int value, List *edges) {
    GraphNode *node = graph_create_node(value, edges);
    list_add(g->nodes, node);
    g->size++;
}

GraphNode *graph_get_node(Graph g, int value) {
    for (int i = 0; i < g.size; i++) {
        GraphNode *node = (GraphNode *) list_get(g.nodes, i);
        if (node->value == value)
            return node;
    }
    return NULL;
}

GraphEdge *graph_get_minimal_edge(GraphNode *node, const int *except) {
    GraphEdge *min = (GraphEdge *) list_get(node->edges, 0);
    for (int i = 1; i < node->edges->size; i++) {
        GraphEdge *edge = (GraphEdge *) list_get(node->edges, i);
        if (except[edge->to] == 0 && edge->weight < min->weight)
            min = edge;
    }
    return min;
}

List *graph_get_all_edges(Graph g) {
    List *edges = list_init();
    for (int i = 0; i < g.size; i++) {
        GraphNode *node = graph_get_node(g, i);
        for (int j = 0; j < node->edges->size; j++) {
            GraphEdge *edge = (GraphEdge *) list_get(node->edges, j);
            list_add(edges, edge);
        }
    }
    return edges;
}

void graph_create_edge(Graph *g, int from, int to, int weight) {
    GraphNode *node = graph_get_node(*g, from);
    GraphEdge *edge = (GraphEdge *) malloc(sizeof(GraphEdge));
    edge->from = from;
    edge->to = to;
    edge->weight = weight;
    if (node->edges == NULL) node->edges = list_init();
    list_add(node->edges, edge);
}

List *graph_get_all_values(Graph *g) {
    List *values = list_init();
    List *nodes = g->nodes;
    for (int i = 0; i < nodes->size; i++) {
        GraphNode *node = list_get(nodes, i);
        list_add(values, node);
    }
    return values;
}

Graph get_graph_from(const Matrix m, const Matrix weights) {
    Graph g = {list_init(), 0};

    for (int i = 0; i < m.n; i++) {
        List *edges = list_init();
        for (int j = 0; j < m.n; j++) {
            if (m.val[i][j] != 1) continue;
            GraphEdge *edge = (GraphEdge *) malloc(sizeof(GraphEdge));
            edge->from = i;
            edge->to = j;
            edge->weight = weights.val[i][j];
            list_add(edges, edge);
        }

        GraphNode *node = graph_create_node(i, edges);
        list_add(g.nodes, node);
    }

    g.size = g.nodes->size;

    return g;
}

void free_graph(Graph *g) {
    for (int i = 0; i < g->size; i++) {
        GraphNode *node = (GraphNode *) list_remove(g->nodes, 0);
        free_list(node->edges);
        node->edges = NULL;
        free(node);
    }
    free(g->nodes);
    g->nodes = NULL;
    g->size = 0;
}