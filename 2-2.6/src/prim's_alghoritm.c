#include <malloc.h>
#include <stdlib.h>
#include "graph/graph.h"

void graph_to_matrix(Graph *g) {
    int **m = (int **) malloc(g->size * sizeof(int *));
    for (int i = 0; i < g->size; i++)
        m[i] = (int *) calloc(g->size, sizeof(int));

    for (int i = 0; i < g->size; i++) {
        GraphNode *cur_node = list_get(g->nodes, i);
        for (int j = 0; j < cur_node->edges->size; j++) {
            GraphEdge *edge = (GraphEdge *) list_get(cur_node->edges, j);
            m[edge->from][edge->to] = edge->weight;
            m[edge->to][edge->from] = edge->weight;
        }
    }

    printf("Graph matrix:\n\n\n");
    for (int i = 0; i < g->size; i++) {
        for (int j = 0; j < g->size; j++)
            printf("%-2d ", m[i][j]);

        printf("\n");
    }

    for (int i = 0; i < g->size; i++)
        free(m[i]);
    free(m);
}

GraphEdge *minimum_edge(Graph spanning_tree, Graph original, const int *visited) {
    GraphEdge *minimal = NULL;
    for (int j = 0; j < spanning_tree.size; j++) {
        GraphNode *cur_node = list_get(spanning_tree.nodes, j);
        GraphNode *node = graph_get_node(original, cur_node->value);

        for (int k = 0; k < node->edges->size; k++) {
            GraphEdge *edge = (GraphEdge *) list_get(node->edges, k);
            if (visited[edge->to] == 0 && (minimal == NULL || edge->weight < minimal->weight))
                minimal = edge;
        }
    }

    return minimal;
}

void minimum_spanning_tree(Graph original) {
    Graph spanning_tree = init_graph();
    int *visited = (int *) calloc(original.size, sizeof(int));

    GraphNode *current = original.nodes->head->value;
    visited[current->value] = 1;
    graph_add_node(&spanning_tree, current->value, list_init());

    for (int i = 0; i < original.size - 1; i++) {
        GraphEdge *minimal = minimum_edge(spanning_tree, original, visited);

        graph_add_node(&spanning_tree, minimal->to, list_init());
        visited[minimal->to] = 1;
        graph_create_edge(&spanning_tree, minimal->from, minimal->to, minimal->weight);
    }

    graph_to_matrix(&spanning_tree);

    free(visited);
    free_graph(&spanning_tree);
}