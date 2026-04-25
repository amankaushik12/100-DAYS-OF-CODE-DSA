#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to find the vertex with the minimum key value that isn't in the MST yet
int minKey(int key[], int mstSet[], int n) {
    int min = INT_MAX, min_index = -1;

    for (int v = 1; v <= n; v++) {
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

int main() {
    int n, m;
    
    // Read number of vertices and edges
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }

    // Dynamically allocate an adjacency matrix for 1-based indexing
    int **graph = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        graph[i] = (int *)malloc((n + 1) * sizeof(int));
        for (int j = 0; j <= n; j++) {
            graph[i][j] = 0;
        }
    }

    // Read edges
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        
        // If there are multiple edges between the same vertices, keep the smallest
        if (graph[u][v] == 0 || w < graph[u][v]) {
            graph[u][v] = w;
            graph[v][u] = w;
        }
    }

    // Arrays to track the minimum weight to connect a node, and whether it's in the MST
    int *key = (int *)malloc((n + 1) * sizeof(int));
    int *mstSet = (int *)malloc((n + 1) * sizeof(int));

    for (int i = 0; i <= n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    // Start with the first vertex
    key[1] = 0;
    long long total_weight = 0;

    // The MST will have exactly n vertices
    for (int count = 0; count < n; count++) {
        // Pick the minimum key vertex not yet included in MST
        int u = minKey(key, mstSet, n);
        
        // If the graph is disconnected and we can't find a valid vertex, break
        if (u == -1) break;

        // Add the picked vertex to the MST Set
        mstSet[u] = 1;
        total_weight += key[u];

        // Update key values of adjacent vertices
        for (int v = 1; v <= n; v++) {
            // Update if: there is an edge, v is not in MST, and the edge weight is smaller than current key[v]
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
            }
        }
    }

    // Print the total weight
    printf("%lld\n", total_weight);

    // Free allocated memory
    for (int i = 0; i <= n; i++) {
        free(graph[i]);
    }
    free(graph);
    free(key);
    free(mstSet);

    return 0;
}