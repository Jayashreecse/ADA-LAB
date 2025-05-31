#include <stdio.h>

#define MAX 100

int main() {
    int n, e, u, v, indeg[MAX] = {0}, adj[MAX][MAX] = {0}, q[MAX], f = 0, r = 0;
    printf("Vertices and edges: ");
    scanf("%d %d", &n, &e);

    printf("Edges (from to):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        indeg[v]++;
    }

    for (int i = 0; i < n; i++)
        if (indeg[i] == 0) q[r++] = i;

    printf("Topological Order: ");
    int count = 0;
    while (f < r) {
        int curr = q[f++];
        printf("%d ", curr);
        count++;

        for (int i = 0; i < n; i++)
            if (adj[curr][i] && --indeg[i] == 0)
                q[r++] = i;
    }

    if (count != n)
        printf("\nCycle detected. No topological order.\n");

    return 0;
}
