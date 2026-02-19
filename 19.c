#include <stdio.h>
#include <stdlib.h>

// Comparison function for qsort
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n;
    // Read the number of elements
    if (scanf("%d", &n) != 1) return 0;

    // Allocate memory for the array
    int *arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    // Read the array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort the array
    qsort(arr, n, sizeof(int), compare);

    int l = 0;
    int r = n - 1;
    
    // Initialize min_sum with the sum of the first and last elements
    // We use long long to prevent potential integer overflow during addition
    long long min_sum = (long long)arr[l] + arr[r];
    if (min_sum < 0) min_sum = -min_sum; // Absolute value
    
    int val_l = arr[l];
    int val_r = arr[r];

    while (l < r) {
        long long current_sum = (long long)arr[l] + arr[r];
        long long abs_current = (current_sum < 0) ? -current_sum : current_sum;

        // Update the result if the current sum is closer to zero
        if (abs_current < min_sum) {
            min_sum = abs_current;
            val_l = arr[l];
            val_r = arr[r];
        }

        // Move pointers
        if (current_sum < 0) {
            l++; // Sum is negative, need a larger sum (move left pointer right)
        } else {
            r--; // Sum is positive, need a smaller sum (move right pointer left)
        }
    }

    // Print the pair
    printf("%d %d\n", val_l, val_r);

    // Free allocated memory
    free(arr);
    return 0;
}