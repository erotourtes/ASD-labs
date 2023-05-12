#include <malloc.h>
#include <stdlib.h>
#include <unistd.h>
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
 * Below is optimised algorithm which uses MinHeap and have time complexity O((E+V)*log(V))
 * ========================================================================================
 */

int compare_nodes(void *a, void *b) {
}

void put_edges(GraphNode *node, MinHeap *heap) {
    ListNode *edges = node->edges->head;

    while ((edges = edges->next) != NULL) {
        GraphEdge *edge = edges->value;
        heap_add(heap, edge);
    }
}

// app points original_matrix circle_radius needed for drawing and don't use in algorithm
void
minimum_spanning_tree_optimised(X11 app, Point *points, Graph original, Matrix original_matrix, int circle_radius) {
    Graph spanning_tree = init_graph();
    int *visited = (int *) calloc(original.size, sizeof(int));
    MinHeap heap = heap_init(compare_nodes);

    GraphNode *current = original.nodes->head->value;
    visited[current->value] = 1;
    graph_add_node(&spanning_tree, current->value, list_init());
    put_edges(current, &heap);

    while (heap.size != 0) {}

    free_graph(&spanning_tree);
    heap_free_heap_only(&heap);
    free(visited);
}
