#include <stdio.h>
#include <stdlib.h>

// Function to perform selection sort
void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;
    
    // Move the boundary of the unsorted subarray one by one
    for (i = 0; i < n - 1; i++) {
        // Find the minimum element in the remaining unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        
        // Swap the found minimum element with the first element of the unsorted part
        if (min_idx != i) {
            temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }
}

int main() {
    int n;

    // 1. Read the number of elements
    if (scanf("%d", &n) != 1) {
        return 1; // Exit if input fails
    }

    // Dynamically allocate memory for the array
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // 2. Read the elements into the array
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 3. Sort the array using Selection Sort
    selectionSort(arr, n);

    // 4. Print the sorted array
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free the allocated memory to prevent leaks
    free(arr);

    return 0;
}