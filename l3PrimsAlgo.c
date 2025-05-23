#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100

int minKey(int key[], bool mstSet[], int n) {
    int min = INT_MAX, min_index = -1;
    for (int i = 0; i < n; i++)
        if (!mstSet[i] && key[i] < min)
            min = key[i], min_index = i;
    return min_index;
}

void primMST(int graph[MAX][MAX], int n) {
    int parent[n], key[n];
    bool mstSet[n];
    for (int i = 0; i < n; i++) key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = true;
        for (int v = 0; v < n; v++)
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    int cost = 0;
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        cost += graph[i][parent[i]];
    }
    printf("Total cost: %d\n", cost);
}

int main() {
    int n, graph[MAX][MAX];
    printf("Vertices: ");
    scanf("%d", &n);
    printf("Adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);
    primMST(graph, n);
    return 0;
}
