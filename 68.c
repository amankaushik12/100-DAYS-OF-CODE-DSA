#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// --- Data Structures ---

// A node for the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Graph structure containing the adjacency list and in-degree array
struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* inDegree;
};

// --- Utility Functions ---

// Function to create a new adjacency list node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with V vertices
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    
    // Allocate memory for adjacency lists and in-degree array
    graph->adjLists = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->inDegree = (int*)calloc(vertices, sizeof(int)); // calloc initializes in-degrees to 0

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

// Function to add a directed edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    // Increment the in-degree of the destination vertex
    graph->inDegree[dest]++;
}

// --- Kahn's Algorithm ---

void topologicalSort(struct Graph* graph) {
    int V = graph->numVertices;
    
    // Simple array-based queue implementation
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    // Array to store the final topological order
    int topoOrder[MAX_VERTICES];
    int topoIndex = 0;

    // Step 1: Enqueue all vertices that currently have an in-degree of 0
    for (int i = 0; i < V; i++) {
        if (graph->inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    // Step 2: Process the queue
    while (front < rear) {
        // Dequeue a vertex
        int u = queue[front++];
        topoOrder[topoIndex++] = u;

        // Iterate through all neighboring vertices of the dequeued vertex u
        struct Node* temp = graph->adjLists[u];
        while (temp != NULL) {
            int v = temp->vertex;
            
            // Decrease the in-degree of the neighbor
            graph->inDegree[v]--;

            // If in-degree becomes 0, add it to the queue
            if (graph->inDegree[v] == 0) {
                queue[rear++] = v;
            }
            temp = temp->next;
        }
    }

    // Step 3: Check for a cycle (If topoIndex doesn't equal total vertices, a cycle exists)
    if (topoIndex != V) {
        printf("Error: The graph contains a cycle. Topological sorting is not possible.\n");
        return;
    }

    // Print the valid topological order
    printf("Topological Sort Order: ");
    for (int i = 0; i < topoIndex; i++) {
        printf("%d ", topoOrder[i]);
    }
    printf("\n");
}

// --- Main Execution ---

int main() {
    int V = 6;
    struct Graph* graph = createGraph(V);

    // Creating a sample Directed Acyclic Graph (DAG)
    // 5 -> 2, 5 -> 0, 4 -> 0, 4 -> 1, 2 -> 3, 3 -> 1
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    topologicalSort(graph);

    // Note: In a production environment, you should include a function 
    // to free the dynamically allocated memory for the graph and its nodes.
    return 0;
}