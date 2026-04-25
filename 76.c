#include <stdio.h>
#include <stdlib.h>

// Node structure for the adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Function to create a new graph node
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to add an undirected edge to the graph
void addEdge(Node** graph, int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph[src];
    graph[src] = newNode;

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph[dest];
    graph[dest] = newNode;
}

// Depth First Search (DFS) function
void dfs(int vertex, Node** graph, int* visited) {
    visited[vertex] = 1; // Mark the current node as visited
    
    Node* temp = graph[vertex];
    // Traverse all adjacent nodes
    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (!visited[connectedVertex]) {
            dfs(connectedVertex, graph, visited);
        }
        temp = temp->next;
    }
}

int main() {
    int n, m;
    
    // Read number of vertices (n) and edges (m)
    if (scanf("%d %d", &n, &m) != 2) return 0;

    // Initialize the adjacency list for the graph (1-indexed)
    Node** graph = (Node**)malloc((n + 1) * sizeof(Node*));
    for (int i = 0; i <= n; i++) {
        graph[i] = NULL;
    }

    // Read the edges
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    // Array to keep track of visited nodes
    int* visited = (int*)calloc((n + 1), sizeof(int));
    int components = 0;

    // Iterate through all nodes from 1 to n
    for (int i = 1; i <= n; i++) {
        // If a node hasn't been visited, it means we found a new component
        if (!visited[i]) {
            components++;
            dfs(i, graph, visited); // Run DFS to mark all nodes in this component
        }
    }

    // Output the total number of connected components
    printf("%d\n", components);

    // Free allocated memory
    for (int i = 1; i <= n; i++) {
        Node* temp = graph[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph);
    free(visited);

    return 0;
}