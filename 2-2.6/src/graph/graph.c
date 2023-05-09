//
// Created by sirmax on 5/9/23.
//

#include "graph.h"
#include <stdlib.h>

Graph get_graph_from(Matrix m, Matrix weights) {
    Graph g = {list_init(), 0};

    for (int i = 0; i < m.n; i++) {
        List *edges = list_init();
        for (int j = 0; j < m.n; i++) {
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

    return g;
}

void clear_graph(Graph *g) {
    for (int i = 0; i < g->size; i++) {
        GraphNode *node = list_remove(g->nodes, i);
        list_clear(node->edges);
        free(node->edges);
        free(node);
    }
    free(g->nodes);
    g->nodes = NULL;
    g->size = 0;
}