#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Global stack for simplicity in this example
int stack[MAX_VERTICES];
int top = -1;

// Function to push an item to the stack
void push(int item) {
    if (top >= MAX_VERTICES - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = item;
}

// Function to pop an item from the stack
int pop() {
    if (top < 0) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack[top--];
}

// Recursive DFS function
void dfs(int vertex, int graph[][MAX_VERTICES], int numVertices, bool visited[]) {
    // Mark the current node as visited
    visited[vertex] = true;

    // Recur for all the vertices adjacent to this vertex
    for (int i = 0; i < numVertices; i++) {
        // If there is a directed edge from 'vertex' to 'i' and 'i' is not visited
        if (graph[vertex][i] == 1 && !visited[i]) {
            dfs(i, graph, numVertices, visited);
        }
    }

    // Push the current vertex to stack which stores the result
    // This happens AFTER all its adjacent vertices are visited
    push(vertex);
}

// Function to perform Topological Sort
void topologicalSort(int graph[][MAX_VERTICES], int numVertices) {
    bool visited[MAX_VERTICES] = {false};
    top = -1; // Reset stack

    // Call the recursive helper function to store Topological
    // Sort starting from all vertices one by one
    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            dfs(i, graph, numVertices, visited);
        }
    }

    // Print the contents of the stack
    printf("Topological Sorting Order: ");
    while (top != -1) {
        printf("%d ", pop());
    }
    printf("\n");
}

int main() {
    int numVertices = 6;
    int graph[MAX_VERTICES][MAX_VERTICES] = {0};

    // Constructing a sample Directed Acyclic Graph (DAG)
    // Edge from u to v is represented by graph[u][v] = 1
    graph[5][2] = 1;
    graph[5][0] = 1;
    graph[4][0] = 1;
    graph[4][1] = 1;
    graph[2][3] = 1;
    graph[3][1] = 1;

    /* Graph looks like this:
       5 ---> 2 ---> 3 ---> 1
       |                    ^
       |                    |
       +---> 0 <--- 4 ------+
    */

    printf("Graph created with %d vertices.\n", numVertices);
    
    topologicalSort(graph, numVertices);

    return 0;
}