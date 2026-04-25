#include <stdio.h>

// Define a large value to represent infinity to prevent integer overflow during addition.
// 1,000,000,000 is safe for 32-bit signed integers.
#define INF 1000000000

int main() {
    int n;
    
    // Read the number of vertices
    if (scanf("%d", &n) != 1) {
        return 1;
    }

    // Using a Variable Length Array (VLA) for the distance matrix
    int dist[n][n];

    // Read the adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
            // Replace -1 with INF (infinity), except for the diagonal where distance is 0
            if (dist[i][j] == -1 && i != j) {
                dist[i][j] = INF;
            }
        }
    }

    // Floyd-Warshall Algorithm core logic
    // k represents the intermediate vertex
    for (int k = 0; k < n; k++) {
        // i represents the source vertex
        for (int i = 0; i < n; i++) {
            // j represents the destination vertex
            for (int j = 0; j < n; j++) {
                // Only update if a path exists through intermediate vertex k
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // Print the final shortest distance matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // If the distance is still INF, there is no path, so print -1
            if (dist[i][j] == INF) {
                printf("-1 ");
            } else {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}