#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int canPlace(int stalls[], int n, int k, int dist) {
    int count = 1;
    int last = stalls[0];

    for (int i = 1; i < n; i++) {
        if (stalls[i] - last >= dist) {
            count++;
            last = stalls[i];
            if (count >= k) return 1;
        }
    }
    return 0;
}

int aggressiveCows(int stalls[], int n, int k) {
    qsort(stalls, n, sizeof(int), compare);

    int low = 1;
    int high = stalls[n - 1] - stalls[0];
    int ans = 0;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (canPlace(stalls, n, k, mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return ans;
}

int main() {
    int stalls[] = {1, 2, 4, 8, 9};
    int n = sizeof(stalls) / sizeof(stalls[0]);
    int k = 3;

    printf("%d\n", aggressiveCows(stalls, n, k));
    return 0;
}