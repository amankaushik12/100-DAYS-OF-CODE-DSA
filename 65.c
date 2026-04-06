#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Adjacency list representation
int adj[MAX_VERTICES][MAX_VERTICES];
int degree[MAX_VERTICES];
bool visited[MAX_VERTICES];

// Function to add an edge to an undirected graph
void addEdge(int u, int v) {
    adj[u][degree[u]++] = v;
    adj[v][degree[v]++] = u;
}

// DFS function that tracks the parent of the current node
bool dfs(int current, int parent) {
    visited[current] = true;

    // Traverse all adjacent vertices of the current vertex
    for (int i = 0; i < degree[current]; i++) {
        int neighbor = adj[current][i];

        // If the neighbor is not visited, recursively call DFS
        if (!visited[neighbor]) {
            if (dfs(neighbor, current)) {
                return true;
            }
        } 
        // If the neighbor is visited AND it is NOT the parent node, we found a cycle
        else if (neighbor != parent) {
            return true;
        }
    }
    return false;
}

// Wrapper function to handle disconnected graphs
bool hasCycle(int vertices) {
    // Initialize all vertices as not visited
    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
    }

    // Call DFS for every unvisited vertex (handles disconnected components)
    for (int i = 0; i < vertices; i++) {
        if (!visited[i]) {
            // Start DFS with -1 as the parent since the starting node has no parent
            if (dfs(i, -1)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    // Initialize degrees to 0
    for(int i = 0; i < MAX_VERTICES; i++) {
        degree[i] = 0;
    }

    int vertices = 5;

    // Example 1: Graph with a cycle
    // 0 -- 1
    // |    |
    // 3 -- 2
    //  \
    //   4
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    addEdge(3, 0); // This edge creates the cycle
    addEdge(3, 4);

    if (hasCycle(vertices)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}