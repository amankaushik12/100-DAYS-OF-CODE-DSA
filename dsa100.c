#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    int index;
};

void merge(struct Node arr[], int count[], int left, int mid, int right) {
    int n = right - left + 1;
    struct Node* temp = (struct Node*)malloc(n * sizeof(struct Node));

    int i = left, j = mid + 1, k = 0;
    int rightCount = 0;

    while (i <= mid && j <= right) {
        if (arr[j].val < arr[i].val) {
            temp[k++] = arr[j++];
            rightCount++;
        } else {
            count[arr[i].index] += rightCount;
            temp[k++] = arr[i++];
        }
    }

    while (i <= mid) {
        count[arr[i].index] += rightCount;
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = 0; i < n; i++) {
        arr[left + i] = temp[i];
    }

    free(temp);
}

void mergeSort(struct Node arr[], int count[], int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, count, left, mid);
    mergeSort(arr, count, mid + 1, right);
    merge(arr, count, left, mid, right);
}

int main() {
    int nums[] = {5, 2, 6, 1};
    int n = sizeof(nums) / sizeof(nums[0]);

    struct Node* arr = (struct Node*)malloc(n * sizeof(struct Node));
    int* count = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        arr[i].val = nums[i];
        arr[i].index = i;
    }

    mergeSort(arr, count, 0, n - 1);

    for (int i = 0; i < n; i++) {
        printf("%d ", count[i]);
    }

    free(arr);
    free(count);
    return 0;
}