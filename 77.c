#include <stdio.h>
#include <stdlib.h>

// Structure for the adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Function to add an undirected edge to the graph
void addEdge(Node** adj, int u, int v) {
    // Add edge from u to v
    Node* newNode1 = (Node*)malloc(sizeof(Node));
    newNode1->vertex = v;
    newNode1->next = adj[u];
    adj[u] = newNode1;

    // Add edge from v to u
    Node* newNode2 = (Node*)malloc(sizeof(Node));
    newNode2->vertex = u;
    newNode2->next = adj[v];
    adj[v] = newNode2;
}

// Depth First Search (DFS) function
void dfs(int v, int* visited, Node** adj) {
    visited[v] = 1; // Mark the current node as visited
    
    Node* temp = adj[v];
    while (temp != NULL) {
        int connectedVertex = temp->vertex;
        if (!visited[connectedVertex]) {
            dfs(connectedVertex, visited, adj);
        }
        temp = temp->next;
    }
}

int main() {
    int n, m;
    
    // Read number of vertices (n) and edges (m)
    if (scanf("%d %d", &n, &m) != 2) return 1;

    // Handle edge cases: 0 nodes or 1 node
    if (n <= 1) {
        printf("CONNECTED\n");
        return 0;
    }

    // Create adjacency list and visited array (1-based indexing)
    Node** adj = (Node**)malloc((n + 1) * sizeof(Node*));
    int* visited = (int*)calloc((n + 1), sizeof(int));

    // Initialize adjacency list
    for (int i = 0; i <= n; i++) {
        adj[i] = NULL;
    }

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(adj, u, v);
    }

    // Start DFS from node 1
    // (Assuming the graph uses 1-based indexing as shown in your sample input)
    dfs(1, visited, adj);

    // Check if all nodes from 1 to n were visited
    int isConnected = 1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            isConnected = 0;
            break; // Found an unvisited node, graph is disconnected
        }
    }

    // Output result
    if (isConnected) {
        printf("CONNECTED\n");
    } else {
        printf("NOT CONNECTED\n");
    }

    // Clean up dynamically allocated memory
    for (int i = 1; i <= n; i++) {
        Node* temp = adj[i];
        while (temp != NULL) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(adj);
    free(visited);

    return 0;
}