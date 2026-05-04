#include <stdio.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int isPossible(int boards[], int n, int k, int maxTime) {
    int painters = 1;
    int curr = 0;

    for (int i = 0; i < n; i++) {
        if (boards[i] > maxTime) return 0;

        if (curr + boards[i] <= maxTime) {
            curr += boards[i];
        } else {
            painters++;
            curr = boards[i];
            if (painters > k) return 0;
        }
    }
    return 1;
}

int minTime(int boards[], int n, int k) {
    int sum = 0, mx = 0;

    for (int i = 0; i < n; i++) {
        sum += boards[i];
        mx = max(mx, boards[i]);
    }

    int low = mx, high = sum, ans = sum;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (isPossible(boards, n, k, mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

int main() {
    int boards[] = {10, 20, 30, 40};
    int n = sizeof(boards) / sizeof(boards[0]);
    int k = 2;

    printf("%d\n", minTime(boards, n, k));
    return 0;
}