#include <malloc.h>
#include "Matrix.h"
#include "../Utils/queue.h"

void dfs_recursive(int *visited, int node, Matrix m) {
    if (visited[node]) return;
    visited[node] = 1;

    printf("%d ", node + 1);

    for (int i = 0; i < m.n; i++)
        if (m.val[node][i] && !visited[i])
            dfs_recursive(visited, i, m);
}

void dfs(Matrix m) {
    int *visited = calloc(m.n, sizeof(int));
    printf("DFS: ");
    dfs_recursive(visited, 3, m);
    printf("\n");
    free(visited);
}

void bfs(Matrix m) {
    Queue queue = get_queue();
    int *visited = calloc(m.n, sizeof(int));

    enqueue(&queue, 3);
    while (queue.size) {
        int node = dequeue(&queue);
        if (visited[node]) continue;
        visited[node] = 1;
        for (int i = 0; i < m.n; i++)
            if (m.val[node][i] && !visited[i]) {
                enqueue(&queue, i);
            }
    }

    printf("\n");

    free_queue(&queue);
}