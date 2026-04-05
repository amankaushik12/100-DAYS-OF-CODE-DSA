#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// --- Data Structures ---

// Structure for an adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Structure for the graph
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

// Structure for the queue
typedef struct Queue {
    int* items;
    int front;
    int rear;
    int size;
} Queue;

// --- Queue Functions ---

Queue* createQueue(int size) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->items = (int*)malloc(size * sizeof(int));
    q->front = -1;
    q->rear = -1;
    q->size = size;
    return q;
}

bool isEmpty(Queue* q) {
    return q->rear == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == q->size - 1) return; // Queue is full
    if (q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) return -1;
    
    int item = q->items[q->front];
    q->front++;
    
    // Reset queue when it becomes empty
    if (q->front > q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    return item;
}

void freeQueue(Queue* q) {
    free(q->items);
    free(q);
}

// --- Graph Functions ---

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));

    // Initialize all adjacency lists as empty and visited array as false
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

// Add an undirected edge (u -> v and v -> u)
void addEdge(Graph* graph, int u, int v) {
    // Add edge from u to v
    Node* newNode = createNode(v);
    newNode->next = graph->adjLists[u];
    graph->adjLists[u] = newNode;

    // Add edge from v to u (Remove this block if the graph is directed)
    newNode = createNode(u);
    newNode->next = graph->adjLists[v];
    graph->adjLists[v] = newNode;
}

// --- BFS Algorithm ---

void bfs(Graph* graph, int startVertex) {
    // 1. Create a queue based on the number of vertices
    Queue* q = createQueue(graph->numVertices);

    // 2. Mark the source node as visited and enqueue it
    graph->visited[startVertex] = true;
    enqueue(q, startVertex);

    printf("BFS Traversal Order: ");

    // 3. Loop until the queue is empty
    while (!isEmpty(q)) {
        // Dequeue a vertex and print it
        int currentVertex = dequeue(q);
        printf("%d ", currentVertex);

        // Iterate through all adjacent vertices of the dequeued vertex
        Node* temp = graph->adjLists[currentVertex];
        while (temp != NULL) {
            int adjVertex = temp->vertex;

            // If an adjacent vertex has not been visited, mark it and enqueue it
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = true;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
    freeQueue(q);
}

// --- Main Execution ---

int main() {
    int n, e, s;

    // Read number of vertices
    printf("Enter the number of vertices (n): ");
    if (scanf("%d", &n) != 1) return 1;

    Graph* graph = createGraph(n);

    // Read the adjacency list (via edges)
    printf("Enter the number of edges: ");
    if (scanf("%d", &e) != 1) return 1;

    printf("Enter the edges (u v) space-separated:\n");
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v); 
    }

    // Read the source vertex
    printf("Enter the source vertex (s): ");
    if (scanf("%d", &s) != 1) return 1;

    // Execute BFS
    bfs(graph, s);

    return 0;
}