#include <stdio.h>

int main() {
    int n, i, j;
    float w[20], p[20], ratio[20], capacity, temp, profit = 0;

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter weights:\n");
    for (i = 0; i < n; i++)
        scanf("%f", &w[i]);

    printf("Enter profits:\n");
    for (i = 0; i < n; i++) {
        scanf("%f", &p[i]);
        ratio[i] = p[i] / w[i];
    }

    // Sort items by ratio in descending order
    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (ratio[i] < ratio[j]) {
                temp = ratio[i]; ratio[i] = ratio[j]; ratio[j] = temp;
                temp = w[i]; w[i] = w[j]; w[j] = temp;
                temp = p[i]; p[i] = p[j]; p[j] = temp;
            }
        }
    }

    printf("Enter knapsack capacity: ");
    scanf("%f", &capacity);

    for (i = 0; i < n && capacity > 0; i++) {
        if (w[i] <= capacity) {
            profit += p[i];
            capacity -= w[i];
        } else {
            profit += ratio[i] * capacity;
            capacity = 0;
        }
    }

    printf("Total Profit: %.2f\n", profit);
    return 0;
}

