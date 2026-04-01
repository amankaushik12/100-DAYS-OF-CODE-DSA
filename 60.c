#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int n;
    
    // Read the number of elements
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    // Dynamically allocate memory for the array
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        // Exit if memory allocation fails
        return 1; 
    }

    // Read the level-order traversal array
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
    }

    bool isMinHeap = true;

    // Check the min-heap property
    // We only need to check up to the last internal node: (n / 2) - 1
    for (int i = 0; i < n / 2; ++i) {
        int left_child = 2 * i + 1;
        int right_child = 2 * i + 2;

        // Check if left child exists and violates the property
        if (left_child < n && arr[i] > arr[left_child]) {
            isMinHeap = false;
            break;
        }

        // Check if right child exists and violates the property
        if (right_child < n && arr[i] > arr[right_child]) {
            isMinHeap = false;
            break;
        }
    }

    // Output the result
    if (isMinHeap) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    // Free the allocated memory to prevent memory leaks
    free(arr);

    return 0;
}