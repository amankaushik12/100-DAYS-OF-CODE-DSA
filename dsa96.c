#include <stdio.h>
#include <stdlib.h>

long long merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left, j = mid, k = left;
    long long inv = 0;

    while (i <= mid - 1 && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv += (mid - i);
        }
    }

    while (i <= mid - 1)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return inv;
}

long long mergeSort(int arr[], int temp[], int left, int right) {
    long long inv = 0;
    if (right > left) {
        int mid = (left + right) / 2;

        inv += mergeSort(arr, temp, left, mid);
        inv += mergeSort(arr, temp, mid + 1, right);
        inv += merge(arr, temp, left, mid + 1, right);
    }
    return inv;
}

int main() {
    int arr[] = {8, 4, 2, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int* temp = (int*)malloc(n * sizeof(int));

    printf("%lld\n", mergeSort(arr, temp, 0, n - 1));

    free(temp);
    return 0;
}