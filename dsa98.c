#include <stdio.h>
#include <stdlib.h>

struct Interval {
    int start;
    int end;
};

int compare(const void* a, const void* b) {
    return ((struct Interval*)a)->start - ((struct Interval*)b)->start;
}

void mergeIntervals(struct Interval arr[], int n) {
    qsort(arr, n, sizeof(struct Interval), compare);

    struct Interval* result = (struct Interval*)malloc(n * sizeof(struct Interval));
    int idx = 0;

    result[idx] = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i].start <= result[idx].end) {
            if (arr[i].end > result[idx].end)
                result[idx].end = arr[i].end;
        } else {
            idx++;
            result[idx] = arr[i];
        }
    }

    for (int i = 0; i <= idx; i++) {
        printf("[%d, %d] ", result[i].start, result[i].end);
    }

    free(result);
}

int main() {
    struct Interval arr[] = {{1,3},{2,6},{8,10},{15,18}};
    int n = sizeof(arr)/sizeof(arr[0]);

    mergeIntervals(arr, n);
    return 0;
}