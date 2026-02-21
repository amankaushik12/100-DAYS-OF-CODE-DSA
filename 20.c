#include <stdio.h>

int main() {
    int n, i, j;
    int arr[100];
    int count = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter array elements:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    for (i = 0; i < n; i++) {
        int sum = 0;
        for (j = i; j < n; j++) {
            sum = sum + arr[j];
            if (sum == 0) {
                count++;
            }
        }
    }

    printf("Number of subarrays with sum zero = %d\n", count);

    return 0;
}