#include <malloc.h>
#include "Utils/deque.h"
#include "matrix/matrix.h"

typedef struct {
    int from;
    int to;
} Edge;

typedef struct {
    Edge *val;
    int count;
} Edges;

int *to_int(int val) {
    int *int_val = malloc(sizeof(int));
    *int_val = val;
    return int_val;
}

int dfs_rec(Matrix m, int *visited, int prev_node, int current_node, Edge *edges, int current_edge_count) {
    visited[current_node] = 1;

    if (prev_node != -1) // if it is not the first node
        edges[current_edge_count++] = (Edge){prev_node, current_node};

    for (int i = 0; i < m.n; i++) {
        if (m.val[current_node][i] && !visited[i]) {
            current_edge_count = dfs_rec(m, visited, current_node, i, edges, current_edge_count);
        }
    }

    edges[current_edge_count++] = (Edge) {current_node, current_node};

    return current_edge_count;
}

Edges dfs(Matrix m, int start_node) {
    Edge *edges = malloc(sizeof(Edge) * (m.n - 1 + m.n)); // max number of edges is n - 1; + n for setting visited
    int *visited = calloc(m.n, sizeof(int));
    int current_edge_count = 0;
    int count = dfs_rec(m, visited, -1, start_node, edges, current_edge_count);
    return (Edges){edges, count};
}

Edges bfs(Matrix m, int start_node) {
    Deque queue = get_deque(sizeof(int));
    Edge *edges = malloc(sizeof(Edge) * (m.n - 1 + m.n)); // max number of edges is n - 1; + n for setting visited
    int current_edge_count = 0;
    int *visited = calloc(m.n, sizeof(int));

    enqueue(&queue, to_int(start_node));
    visited[start_node] = 1;
    while (queue.size) {
        int *node = (int *) dequeue(&queue);

        for (int i = 0; i < m.n; i++) {
            if (m.val[*node][i] && !visited[i]) {
                edges[current_edge_count++] = (Edge){ *node, i };

                enqueue(&queue, to_int(i));
                visited[i] = 1;
            }
        }
        edges[current_edge_count++] = (Edge){ *node, *node };
        free(node);
    }

    free_deque(&queue);
    free(visited);

    return (Edges){edges, current_edge_count};
}