#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include "graph/graph.h"
#include "Utils/MinHeap.h"

GraphEdge *minimum_edge(Graph spanning_tree, Graph original, const int *visited) {
    GraphEdge *minimal = NULL;
    ListNode *cur_list_node = NULL;
    list_next(NULL);
    while ((cur_list_node = list_next(spanning_tree.nodes)) != NULL) { // Iterator in C
        int value = ((GraphNode *) cur_list_node->value)->value;
        GraphNode *cur_node = graph_get_node(original, value);
        for (int k = 0; k < cur_node->edges->size; k++) {
            GraphEdge *edge = (GraphEdge *) list_get(cur_node->edges, k);
            if (visited[edge->to->value] == 0 && (minimal == NULL || edge->weight < minimal->weight))
                minimal = edge;
        }
    }

    return minimal;
}

void halt(X11 app, Matrix original_matrix, Point *points, GraphEdge *minimal, int circle_radius) {
    draw_graph_edge(app, original_matrix, points, *minimal, circle_radius);
    draw_weight_count(app, minimal->weight);
    scanf("%*c");
    XFlush(app.dis);
}

// app points original_matrix circle_radius needed for drawing and don't use in algorithm
void minimum_spanning_tree(X11 app, Point *points, Graph original, Matrix original_matrix, int circle_radius) {
    Graph spanning_tree = init_graph();
    int *visited = (int *) calloc(original.size, sizeof(int));

    GraphNode *current = original.nodes->head->value;
    visited[current->value] = 1;
    graph_add_node(&spanning_tree, current->value, list_init());

    for (int i = 0; i < original.size - 1; i++) {
        GraphEdge *minimal = minimum_edge(spanning_tree, original, visited);

        visited[minimal->to->value] = 1;
        GraphNode *to = graph_add_node(&spanning_tree, minimal->to->value, list_init());
        GraphNode *from = graph_get_node(spanning_tree, minimal->from->value);
        graph_create_edge(&spanning_tree, from, to, minimal->weight);

        halt(app, original_matrix, points, minimal, circle_radius);
    }

    free(visited);
    free_graph(&spanning_tree);
}

/* ========================================================================================
 * Below is optimised algorithm but still is not optimal (O(log(V)(V+E)
 * ========================================================================================
 */

void
minimum_spanning_tree_optimised(X11 app, Point *points, Graph original, Matrix original_matrix, int circle_radius) {
    Graph spanning_tree = init_graph();
    int *visited = (int *) calloc(original.size, sizeof(int));
    GraphNode **nodes = calloc(original.size, sizeof(GraphNode *));
    GraphNode **parents = calloc(original.size, sizeof(GraphNode *));
    int *weights = (int *) calloc(original.size, sizeof(int));

    // O(V)
    for (int i = 0; i < original.size; i++) {
        nodes[i] = graph_get_node(original, i);
        weights[i] = i == 0 ? 0 : INT32_MAX;
    }

    // O(V)
    for (int i = 0; i < original.size; i++) {
        // find min unvisited edge edge
        // O(V)
        int min = INT32_MAX;
        int min_parent = -1;
        for (int j = 0; j < original.size; j++) {
            if (visited[j] == 0 && weights[j] < min) {
                min = weights[j];
                min_parent = j;
            }
        }

        // set it visited
        visited[min_parent] = 1;
        GraphNode *parent = nodes[min_parent];

        // update all neighbours
        // O(E)
        for (int j = 0; j < parent->edges->size; j++) {
            GraphEdge *edge = (GraphEdge *) list_get(parent->edges, j);
            if (visited[edge->to->value] == 0 && edge->weight < weights[edge->to->value]) {
                parents[edge->to->value] = parent;
                weights[edge->to->value] = edge->weight;
            }
        }

        if (i == 0) continue;
        GraphEdge *edge = malloc(sizeof(GraphEdge));
        edge->from = parents[parent->value];
        edge->to = parent;
        edge->weight = weights[min_parent];
        halt(app, original_matrix, points, edge, circle_radius);
        free(edge);
    }

    // O(V) * (O(V) + O(E))
    free(weights);
    free(nodes);
    free(parents);
    free_graph(&spanning_tree);
    free(visited);
}