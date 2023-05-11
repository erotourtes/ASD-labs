#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include "graph/graph.h"

GraphEdge *minimum_edge(Graph spanning_tree, Graph original, const int *visited) {
    GraphEdge *minimal = NULL;
    ListNode *cur_listNode = NULL;
    while((cur_listNode = list_next(spanning_tree.nodes)) != NULL) { // Iterator in C
        GraphNode *cur_node = cur_listNode->value;
        GraphNode *node = graph_get_node(original, cur_node->value);

        for (int k = 0; k < node->edges->size; k++) {
            GraphEdge *edge = (GraphEdge *) list_get(node->edges, k);
            if (visited[edge->to] == 0 && (minimal == NULL || edge->weight < minimal->weight))
                minimal = edge;
        }
    }

    return minimal;
}

void halt(X11 app, Matrix original_matrix, Point *points, GraphEdge *minimal, int circle_radius) {
    draw_graph_edge(app, original_matrix, points, *minimal, circle_radius);
    scanf("%*c");
    XFlush(app.dis);
}

void minimum_spanning_tree(X11 app, Point *points, Graph original, Matrix original_matrix, int circle_radius) {
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

        halt(app, original_matrix, points, minimal, circle_radius);
    }

    free(visited);
    free_graph(&spanning_tree);
}