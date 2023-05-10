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

void graph_create_edge(Graph *g, int from, int to, int weight) {
    GraphNode *node = graph_get_node(*g, from);
    GraphEdge *edge = (GraphEdge *) malloc(sizeof(GraphEdge));
    edge->from = from;
    edge->to = to;
    edge->weight = weight;
    if (node->edges == NULL) node->edges = list_init();
    list_add(node->edges, edge);
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