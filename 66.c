#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for adjacency list
struct Node {
    int dest;
    struct Node* next;
};

// Adjacency list structure
struct AdjList {
    struct Node* head;
};

// Graph structure
struct Graph {
    int V; // Number of vertices
    struct AdjList* array;
};

// Helper function to create a new adjacency list node
struct Node* newAdjListNode(int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Helper function to create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }
    return graph;
}

// Function to add a directed edge from src to dest
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// DFS utility function to detect a cycle
bool isCyclicUtil(struct Graph* graph, int v, bool visited[], bool recStack[]) {
    if (!visited[v]) {
        // Mark the current node as visited and add it to the recursion stack
        visited[v] = true;
        recStack[v] = true;

        // Traverse all adjacent vertices
        struct Node* temp = graph->array[v].head;
        while (temp != NULL) {
            int adj = temp->dest;

            // If the adjacent node is not visited, recursively visit it
            if (!visited[adj] && isCyclicUtil(graph, adj, visited, recStack)) {
                return true;
            }
            // If the adjacent node is already in the recursion stack, a cycle exists
            else if (recStack[adj]) {
                return true;
            }
            temp = temp->next;
        }
    }
    
    // Remove the vertex from recursion stack before returning
    recStack[v] = false;
    return false;
}

// Function to check if the graph contains a cycle
bool isCyclic(struct Graph* graph) {
    // Allocate and initialize visited and recStack arrays to false
    bool* visited = (bool*)calloc(graph->V, sizeof(bool));
    bool* recStack = (bool*)calloc(graph->V, sizeof(bool));

    // Call the recursive helper for each unvisited node (handles disconnected graphs)
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i] && isCyclicUtil(graph, i, visited, recStack)) {
            free(visited);
            free(recStack);
            return true;
        }
    }

    free(visited);
    free(recStack);
    return false;
}

int main() {
    int V = 4;
    struct Graph* graph = createGraph(V);

    // Creating a directed graph:
    // 0 -> 1
    // 0 -> 2
    // 1 -> 2
    // 2 -> 0 (This creates a cycle 0 -> 2 -> 0)
    // 2 -> 3
    
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0); 
    addEdge(graph, 2, 3);

    if (isCyclic(graph)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}