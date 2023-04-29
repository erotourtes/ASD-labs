#include <malloc.h>
#include "Utils/queue.h"
#include "matrix/matrix.h"

typedef struct {
    int from;
    int to;
} Edge;

typedef struct {
    Edge *val;
    int count;
} Edges;

void dfs_recursive(int *visited, int node, Matrix m) {
    if (visited[node]) return;
    visited[node] = 1;

    printf("%d ", node + 1);

    for (int i = 0; i < m.n; i++)
        if (m.val[node][i] && !visited[i])
            dfs_recursive(visited, i, m);
}

Edges dfs(Matrix m, int start_node) {
    int *visited = calloc(m.n, sizeof(int));
    printf("DFS: ");
    dfs_recursive(visited, 3, m);
    printf("\n");
    free(visited);
}


int *to_int(int val) {
    int *int_val = malloc(sizeof(int));
    *int_val = val;
    return int_val;
}

Edges bfs(Matrix m, int start_node) {
    Queue queue = get_queue(sizeof(int));
    Edge *edges = malloc(sizeof(Edge) * (m.n - 1 + m.n)); // max number of edges is n - 1; + n for setting visited
    int current_edge_count = 0;
    int *visited = calloc(m.n, sizeof(int));

    enqueue(&queue, to_int(start_node));
    visited[start_node] = 1;
    while (queue.size) {
        int *node = (int *) dequeue(&queue);
//        printf("from %d \n", *node + 1);

        for (int i = 0; i < m.n; i++) {
            if (m.val[*node][i] && !visited[i]) {
//                printf("\tto %d\n", i + 1);
                edges[current_edge_count++] = (Edge){ *node, i };

                enqueue(&queue, to_int(i));
                visited[i] = 1;
            }
        }
        edges[current_edge_count++] = (Edge){ *node, *node };
        free(node);
    }

    free_queue(&queue);
    free(visited);

    return (Edges){edges, current_edge_count};
}