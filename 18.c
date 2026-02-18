#include <stdio.h>

// Function to reverse a portion of the array from index 'start' to 'end'
void reverse(int arr[], int start, int end) {
    while (start < end) {
        // Swap elements at start and end
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        
        // Move pointers towards the center
        start++;
        end--;
    }
}

int main() {
    int n;
    
    // 1. Read the size of the array
    if (scanf("%d", &n) != 1) return 0;

    // Handle edge case for empty array
    if (n <= 0) {
        printf("\n");
        return 0;
    }

    int arr[n];
    
    // 2. Read the array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int k;
    // 3. Read the number of rotations (k)
    scanf("%d", &k);

    // Optimization: If k is larger than n, the effective rotations is k % n
    // Example: Rotating an array of size 5 by 7 times is same as rotating it 2 times.
    k = k % n;

    // Logic for Right Rotation using Reversal Algorithm:
    // Step A: Reverse the entire array
    reverse(arr, 0, n - 1);
    
    // Step B: Reverse the first k elements
    reverse(arr, 0, k - 1);
    
    // Step C: Reverse the remaining elements (from k to n-1)
    reverse(arr, k, n - 1);

    // 4. Print the rotated array
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}