#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int isPossible(int arr[], int n, int m, int maxPages) {
    int students = 1;
    int pages = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] > maxPages) return 0;

        if (pages + arr[i] <= maxPages) {
            pages += arr[i];
        } else {
            students++;
            pages = arr[i];
            if (students > m) return 0;
        }
    }
    return 1;
}

int allocateBooks(int arr[], int n, int m) {
    if (m > n) return -1;

    int sum = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
        mx = max(mx, arr[i]);
    }

    int low = mx, high = sum, ans = sum;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (isPossible(arr, n, m, mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

int main() {
    int arr[] = {12, 34, 67, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int m = 2;

    printf("%d\n", allocateBooks(arr, n, m));
    return 0;
}