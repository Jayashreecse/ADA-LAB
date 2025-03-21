#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge function to merge two sub-arrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of the left sub-array
    int n2 = right - mid;    // Size of the right sub-array
    int leftArr[n1], rightArr[n2];

    // Copy the left and right sub-arrays
    for (int i = 0; i < n1; i++)  
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)  
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    
    // Merging the two sorted sub-arrays
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy any remaining elements from leftArr (if any)
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy any remaining elements from rightArr (if any)
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Merge Sort function to divide the array
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;  // Find the midpoint

        mergeSort(arr, left, mid);  // Recursively sort the left sub-array
        mergeSort(arr, mid + 1, right);  // Recursively sort the right sub-array

        merge(arr, left, mid, right);  // Merge the two sorted sub-arrays
    }
}

int main() {
    int N;
    printf("Enter the number of elements (N): ");
    scanf("%d", &N);  // Input the number of elements

    int arr[N];

    // Generating random numbers
    srand(time(NULL));  // Seed the random number generator with the current time
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 1000;  // Generate random number between 0 and 999
    }

    // Print the original array
    printf("Original array: \n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Time measurement before sorting
    clock_t start = clock();

    // Perform merge sort
    mergeSort(arr, 0, N - 1);

    // Time measurement after sorting
    clock_t end = clock();
    
    // Print the sorted array
    printf("Sorted array: \n");
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Calculate and print the time taken (in milliseconds)
    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;  // Convert to milliseconds
    printf("Time taken to sort the array: %.6f milliseconds\n", time_taken);

    return 0;
}
