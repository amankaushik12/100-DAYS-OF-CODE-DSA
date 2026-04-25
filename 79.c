#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// ---------------------------------------------------------
// Graph Adjacency List Definitions
// ---------------------------------------------------------
typedef struct Node {
    int dest;
    int weight;
    struct Node* next;
} Node;

// ---------------------------------------------------------
// Min-Heap (Priority Queue) Definitions
// ---------------------------------------------------------
typedef struct {
    int vertex;
    int distance;
} HeapNode;

typedef struct {
    HeapNode* array;
    int size;
    int capacity;
} MinHeap;

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Push a new distance for a vertex into the min-heap
void push(MinHeap* heap, int vertex, int distance) {
    if (heap->size == heap->capacity) return; // Prevent overflow
    
    int i = heap->size++;
    heap->array[i].vertex = vertex;
    heap->array[i].distance = distance;

    // Fix the min-heap property by bubbling up
    while (i != 0 && heap->array[(i - 1) / 2].distance > heap->array[i].distance) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Extract the minimum distance vertex from the min-heap
HeapNode pop(MinHeap* heap) {
    if (heap->size <= 0) return (HeapNode){-1, -1};
    if (heap->size == 1) return heap->array[--heap->size];

    HeapNode root = heap->array[0];
    heap->array[0] = heap->array[--heap->size];

    // Fix the min-heap property by bubbling down
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size && heap->array[left].distance < heap->array[smallest].distance)
            smallest = left;
        if (right < heap->size && heap->array[right].distance < heap->array[smallest].distance)
            smallest = right;

        if (smallest != i) {
            swap(&heap->array[i], &heap->array[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return root;
}

// ---------------------------------------------------------
// Main Function
// ---------------------------------------------------------
int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 1;

    // Allocate adjacency list (1-based indexing for vertices 1 to n)
    Node** adj = (Node**)calloc(n + 1, sizeof(Node*));

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        
        // Add directed edge u -> v
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->dest = v;
        newNode->weight = w;
        newNode->next = adj[u];
        adj[u] = newNode;

        // NOTE: If the graph is undirected, uncomment the lines below:
        /*
        Node* revNode = (Node*)malloc(sizeof(Node));
        revNode->dest = u;
        revNode->weight = w;
        revNode->next = adj[v];
        adj[v] = revNode;
        */
    }

    int source;
    scanf("%d", &source);

    // Initialize distances to infinity (INT_MAX)
    int* dist = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }
    dist[source] = 0;

    // Initialize Min-Heap
    MinHeap heap;
    // Capacity bounded by edges + 1 due to lazy deletion strategy
    heap.capacity = m + n; 
    heap.size = 0;
    heap.array = (HeapNode*)malloc(heap.capacity * sizeof(HeapNode));

    // Start Dijkstra's algorithm
    push(&heap, source, 0);

    while (heap.size > 0) {
        HeapNode current = pop(&heap);
        int u = current.vertex;
        int d = current.distance;

        // Lazy deletion: If we've already found a shorter path, ignore this stale record
        if (d > dist[u]) continue;

        // Traverse neighbors
        Node* temp = adj[u];
        while (temp != NULL) {
            int v = temp->dest;
            int weight = temp->weight;

            // Relaxation step
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                push(&heap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    // Print the computed shortest distances
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) {
            printf("-1 "); // Standard fallback for unreachable vertices
        } else {
            printf("%d ", dist[i]);
        }
    }
    printf("\n");

    // Clean up allocated memory
    for (int i = 1; i <= n; i++) {
        Node* temp = adj[i];
        while (temp != NULL) {
            Node* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    free(adj);
    free(dist);
    free(heap.array);

    return 0;
}