
MERGE SORT

 #include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) 
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) 
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) 
        arr[k++] = L[i++];
    while (j < n2) 
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int N;
    printf("Enter number of elements: ");
    scanf("%d", &N);

    int arr[N];
    srand((unsigned)time(NULL));
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 1000;

    clock_t start = clock();
    mergeSort(arr, 0, N - 1);
    clock_t end = clock();

    // Print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    double timeTaken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    printf("Time taken: %.4f ms\n", timeTaken);

    return 0;
}




QUICK SORT

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1, temp;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int N;
    printf("Enter number of elements: ");
    scanf("%d", &N);

    int arr[N];
    srand(time(0));
    for (int i = 0; i < N; i++)
        arr[i] = rand() % 1000;

    clock_t start = clock();
    quickSort(arr, 0, N - 1);
    clock_t end = clock();

    printf("Time taken: %.4f ms\n", ((double)(end - start) / CLOCKS_PER_SEC) * 1000);
    return 0;
}




 PRIMS ALGO

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



KRUSKAL ALGO

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



 KNAPSACK 0/1

#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, W;
    printf("Enter number of items and max weight: ");
    scanf("%d %d", &n, &W);

    int w[n], v[n];
    printf("Enter weight and value of each item:\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d", &w[i], &v[i]);

    int dp[n+1][W+1];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (w[i-1] <= j)
                dp[i][j] = max(v[i-1] + dp[i-1][j - w[i-1]], dp[i-1][j]);
            else
                dp[i][j] = dp[i-1][j];
        }
    }

    printf("Max value: %d\n", dp[n][W]);
    return 0;
}

TOPOLOGICAL ORDER USING BFS

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
NQUEENS

#include <stdio.h>
#define MAX 20

int board[MAX][MAX], N;

int isSafe(int row, int col) {
    int i, j;
    for (i = 0; i < col; i++)
        if (board[row][i]) return 0;
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j]) return 0;
    for (i = row, j = col; i < N && j >= 0; i++, j--)
        if (board[i][j]) return 0;
    return 1;
}

int solveNQUtil(int col) {
    if (col >= N) return 1;
    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;
            if (solveNQUtil(col + 1)) return 1;
            board[i][col] = 0;
        }
    }
    return 0;
}

void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%c ", board[i][j] ? 'Q' : '.');
        printf("\n");
    }
}

int main() {
    printf("Enter number of queens (4 to 20): ");
    if (scanf("%d", &N) != 1 || N < 4 || N > 20) {
        printf("Invalid input!\n");
        return 1;
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    if (solveNQUtil(0)) {
        printf("One of the solutions:\n");
        printBoard();
    } else {
        printf("No solution exists for %d queens.\n", N);
    }











KNAPSACK_GREEDY

#include <stdio.h>

typedef struct {
    float value, weight;
} Item;

void fractionalKnapsack(Item items[], int n, float capacity) {
    float totalValue = 0, remain = capacity;

    // Calculate value-to-weight ratio
    float ratio[n];
    for (int i = 0; i < n; i++)
        ratio[i] = items[i].value / items[i].weight;

    // Simple selection sort by ratio descending
    for (int i = 0; i < n -1; i++) {
        for (int j = i +1; j < n; j++) {
            if (ratio[j] > ratio[i]) {
                float tempR = ratio[i]; ratio[i] = ratio[j]; ratio[j] = tempR;
                Item tempI = items[i]; items[i] = items[j]; items[j] = tempI;
            }
        }
    }

    for (int i = 0; i < n && remain > 0; i++) {
        if (items[i].weight <= remain) {
            remain -= items[i].weight;
            totalValue += items[i].value;
            printf("Taken whole item %.2f\n", items[i].value);
        } else {
            float frac = remain / items[i].weight;
            totalValue += items[i].value * frac;
            printf("Taken %.2f fraction of item %.2f\n", frac, items[i].value);
            remain = 0;
        }
    }

    printf("Total value = %.2f\n", totalValue);
}

int main() {
    int n;
    float capacity;
    printf("Number of items: ");
    scanf("%d", &n);

    Item items[n];
    for (int i = 0; i < n; i++) {
        printf("Value of item %d: ", i + 1);
        scanf("%f", &items[i].value);
        printf("Weight of item %d: ", i + 1);
        scanf("%f", &items[i].weight);
    }

    printf("Knapsack capacity: ");
    scanf("%f", &capacity);

    fractionalKnapsack(items, n, capacity);
    return 0;
}








JOHNS_TROTTER

#include <stdio.h>
#define L -1
#define R 1

void print(int a[], int d[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d%s ", a[i], d[i] == L ? "<" : ">");
    printf("\n");
}

int getMobile(int a[], int d[], int n) {
    int m = 0;
    for (int i = 0; i < n; i++)
        if ((d[i] == L && i > 0 && a[i] > a[i-1]) ||
            (d[i] == R && i < n-1 && a[i] > a[i+1]))
            if (a[i] > m) m = a[i];
    return m;
}

int pos(int a[], int n, int val) {
    for (int i = 0; i < n; i++) if (a[i] == val) return i;
    return -1;
}

void jt(int n) {
    int a[n], d[n];
    for (int i = 0; i < n; i++) a[i] = i+1, d[i] = L;
    print(a, d, n);

    while (1) {
        int m = getMobile(a, d, n);
        if (m == 0) break;
        int p = pos(a, n, m), q = (d[p] == L) ? p - 1 : p + 1;

        int t = a[p]; a[p] = a[q]; a[q] = t;
        t = d[p]; d[p] = d[q]; d[q] = t;

        for (int i = 0; i < n; i++)
            if (a[i] > m) d[i] *= -1;

        print(a, d, n);
    }
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    jt(n);
    return 0;
}







HEAPS


#include <stdio.h>

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function
void heapify(int arr[], int n, int i) {
    int largest = i;          // Initialize largest as root
    int left = 2 * i + 1;     // left = 2*i + 1
    int right = 2 * i + 2;    // right = 2*i + 2

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Main function to perform heap sort
void heapSort(int arr[], int n) {
    // Build a max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract elements from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Function to print the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[i]);

    printf("Original array:\n");
    printArray(arr, n);

    heapSort(arr, n);

    printf("Sorted array using Heap Sort:\n");
    printArray(arr, n);

    return 0;
}









FLYODS

#include <stdio.h>
#define MAX 10
#define INF 9999

void floydWarshall(int graph[MAX][MAX], int n) {
    int dist[MAX][MAX];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = graph[i][j];

    // Floyd-Warshall algorithm
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    // Print shortest distance matrix
    printf("Shortest distances between every pair of vertices:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf(" INF");
            else
                printf("%4d", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n, graph[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (0 for no edge, except diagonal):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (i != j && graph[i][j] == 0)
                graph[i][j] = INF;
        }

    floydWarshall(graph, n);

    return 0;
}








DJIKRSTRASS


#include <stdio.h>
#define INF 9999
#define MAX 10

void dijkstra(int graph[MAX][MAX], int n, int src) {
    int dist[MAX], visited[MAX] = {0}, i, j, u, minDist;

    for (i = 0; i < n; i++)
        dist[i] = INF;
    dist[src] = 0;

    for (i = 0; i < n; i++) {
        minDist = INF;
        for (j = 0; j < n; j++)
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }

        visited[u] = 1;

        for (j = 0; j < n; j++)
            if (!visited[j] && graph[u][j] && dist[u] + graph[u][j] < dist[j])
                dist[j] = dist[u] + graph[u][j];
    }

    printf("Distances from vertex %d:\n", src);
    for (i = 0; i < n; i++)
        printf("%d -> %d = %d\n", src, i, dist[i]);
}

int main() {
    int n, src, i, j, graph[MAX][MAX];

    printf("Vertices count: ");
    scanf("%d", &n);

    printf("Adjacency matrix (0 = no edge):\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == 0 && i != j)
                graph[i][j] = INF;
        }

    printf("Source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, n, src);
    return 0;
}

Merge sort

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int N;
    printf("Enter number of elements: ");
    scanf("%d", &N);

    int arr[N];
    // Instead of rand(), read each element from the user:
    printf("Enter %d integers (separated by spaces or newlines):\n", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    // Time the sort:
    clock_t start = clock();
       mergeSort(arr, 0, N - 1);
    clock_t end = clock();

    // Print the sorted array:
    printf("Sorted array: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Print elapsed time in milliseconds:
    double timeTaken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    printf("Time taken: %.4f ms\n", timeTaken);

    return 0;
}

}
  


