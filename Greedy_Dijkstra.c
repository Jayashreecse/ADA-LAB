#include <stdio.h>
#define INF 9999
#define MAX 10

void dijkstra(int graph[MAX][MAX], int n, int src) {
    int dist[MAX], visited[MAX] = {0}, i, j, min, u;

    // Initialize distances
    for (i = 0; i < n; i++)
        dist[i] = INF;
    dist[src] = 0;

    for (i = 0; i < n - 1; i++) {
        min = INF;

        // Find the unvisited node with the smallest distance
        for (j = 0; j < n; j++)
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }

        visited[u] = 1;

        // Update distances of neighbors
        for (j = 0; j < n; j++)
            if (graph[u][j] && !visited[j] && dist[u] + graph[u][j] < dist[j])
                dist[j] = dist[u] + graph[u][j];
    }

    // Print result
    printf("\nShortest distances from vertex %d:\n", src);
    for (i = 0; i < n; i++)
        printf("To %d: %d\n", i, dist[i]);
}

int main() {
    int n, i, j, graph[MAX][MAX], src;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j)
                graph[i][j] = INF;
        }

    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &src);

    dijkstra(graph, n, src);

    return 0;
}

