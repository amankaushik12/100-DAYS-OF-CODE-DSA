#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure for the graph
struct Graph {
    int numVertices;
    struct Node** adjLists; // Array of pointers to linked lists
    int* visited;           // Array to keep track of visited vertices
};

// Function to create a new adjacency list node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to initialize a graph with 'n' vertices
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    // Initialize all adjacency lists as empty and all vertices as unvisited
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Function to add a directed edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    // Note: If this is an undirected graph, you would also add:
    // newNode = createNode(src);
    // newNode->next = graph->adjLists[dest];
    // graph->adjLists[dest] = newNode;
}

// Recursive DFS function
void DFS(struct Graph* graph, int vertex) {
    // Mark the current vertex as visited and print it
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    // Get the adjacency list for the current vertex
    struct Node* temp = graph->adjLists[vertex];

    // Traverse all adjacent vertices
    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        // If the adjacent vertex hasn't been visited, recursively call DFS on it
        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next; // Move to the next adjacent node
    }
}

int main() {
    int n, edges, u, v, s;

    // 1. Input: n (number of vertices)
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);

    struct Graph* graph = createGraph(n);

    // 2. Input: Adjacency list (built via edges)
    printf("Enter number of directed edges: ");
    scanf("%d", &edges);

    printf("Enter the edges (source destination) separated by space:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    // 3. Input: starting vertex s
    printf("Enter starting vertex (s): ");
    scanf("%d", &s);

    // 4. Output: DFS traversal order
    printf("DFS traversal order starting from vertex %d: ", s);
    DFS(graph, s);
    printf("\n");

    return 0;
}