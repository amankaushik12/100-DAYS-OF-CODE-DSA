#include <stdio.h>
#include <stdlib.h>

struct Interval {
    int start;
    int end;
};

int compareStart(const void* a, const void* b) {
    return ((struct Interval*)a)->start - ((struct Interval*)b)->start;
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void heapifyUp(int heap[], int index) {
    while (index > 0 && heap[(index - 1) / 2] > heap[index]) {
        swap(&heap[(index - 1) / 2], &heap[index]);
        index = (index - 1) / 2;
    }
}

void heapifyDown(int heap[], int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && heap[left] < heap[smallest]) smallest = left;
    if (right < size && heap[right] < heap[smallest]) smallest = right;

    if (smallest != index) {
        swap(&heap[index], &heap[smallest]);
        heapifyDown(heap, size, smallest);
    }
}

void insertHeap(int heap[], int* size, int value) {
    heap[*size] = value;
    (*size)++;
    heapifyUp(heap, *size - 1);
}

void removeMin(int heap[], int* size) {
    heap[0] = heap[*size - 1];
    (*size)--;
    heapifyDown(heap, *size, 0);
}

int minMeetingRooms(struct Interval arr[], int n) {
    qsort(arr, n, sizeof(struct Interval), compareStart);

    int* heap = (int*)malloc(n * sizeof(int));
    int size = 0;

    insertHeap(heap, &size, arr[0].end);

    for (int i = 1; i < n; i++) {
        if (arr[i].start >= heap[0]) {
            removeMin(heap, &size);
        }
        insertHeap(heap, &size, arr[i].end);
    }

    free(heap);
    return size;
}

int main() {
    struct Interval arr[] = {{0,30},{5,10},{15,20}};
    int n = sizeof(arr)/sizeof(arr[0]);

    printf("%d\n", minMeetingRooms(arr, n));
    return 0;
}