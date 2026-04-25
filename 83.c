#include <stdio.h>
#include <stdlib.h>

// Function to find the Lower Bound
// Returns the index of the first element >= x
int lower_bound(int arr[], int n, int x) {
    int low = 0;
    int high = n - 1;
    int ans = n; // Default if all elements are less than x

    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] >= x) {
            ans = mid;      // Found a candidate, store it
            high = mid - 1; // Continue searching on the left for a smaller index
        } else {
            low = mid + 1;  // Target is strictly greater, search on the right
        }
    }
    return ans;
}

// Function to find the Upper Bound
// Returns the index of the first element > x
int upper_bound(int arr[], int n, int x) {
    int low = 0;
    int high = n - 1;
    int ans = n; // Default if no element is strictly greater than x

    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if (arr[mid] > x) {
            ans = mid;      // Found a candidate, store it
            high = mid - 1; // Continue searching on the left for a smaller index
        } else {
            low = mid + 1;  // Target is >= current element, search on the right
        }
    }
    return ans;
}

int main() {
    int n, x;

    // Read the size of the array
    if (scanf("%d", &n) != 1) return 1;

    // Dynamically allocate memory for the array
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read the sorted array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Read the target value
    if (scanf("%d", &x) != 1) {
        free(arr);
        return 1;
    }

    // Calculate bounds
    int lb_index = lower_bound(arr, n, x);
    int ub_index = upper_bound(arr, n, x);

    // Print the result
    printf("%d %d\n", lb_index, ub_index);

    // Free allocated memory
    free(arr);

    return 0;
}