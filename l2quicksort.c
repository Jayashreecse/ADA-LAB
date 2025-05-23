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
