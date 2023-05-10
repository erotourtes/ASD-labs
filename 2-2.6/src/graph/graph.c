//
// Created by sirmax on 5/9/23.
//

#include "graph.h"
#include <stdlib.h>

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

        GraphNode *node = (GraphNode *) malloc(sizeof(GraphNode));
        node->value = i;
        node->edges = edges;
        list_add(g.nodes, node);
    }

    g.size = g.nodes->size;

    return g;
}

void free_graph(Graph *g) {
    for (int i = 0; i < g->size; i++) {
        GraphNode *node = (GraphNode *) list_remove(g->nodes, 0);
        list_clear(node->edges);
        node->edges = NULL;
        free(node);
    }
    free(g->nodes);
    g->nodes = NULL;
    g->size = 0;
}