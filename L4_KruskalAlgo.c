#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int u, v, w;
} Edge;

int parent[MAX];

int find(int i) {
    if (i == parent[i]) return i;
    return parent[i] = find(parent[i]);
}

void unionSet(int a, int b) {
    parent[find(a)] = find(b);
}

int cmp(const void *a, const void *b) {
    return ((Edge *)a)->w - ((Edge *)b)->w;
}

int main() {
    int n, e;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &n, &e);

    Edge edges[e];
    printf("Enter edges (u v weight):\n");
    for (int i = 0; i < e; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

    for (int i = 0; i < n; i++) parent[i] = i;

    qsort(edges, e, sizeof(Edge), cmp);

    int cost = 0;
    printf("Edge \tWeight\n");
    for (int i = 0, count = 0; count < n - 1 && i < e; i++) {
        int u = edges[i].u, v = edges[i].v, w = edges[i].w;
        if (find(u) != find(v)) {
            unionSet(u, v);
            printf("%d - %d \t%d\n", u, v, w);
            cost += w;
            count++;
        }
    }

    printf("Total cost: %d\n", cost);
    return 0;
}
