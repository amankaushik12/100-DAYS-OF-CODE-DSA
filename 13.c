#include <stdio.h>
#include <stdlib.h>

int main() {
    int r, c;

    // Read the number of rows (r) and columns (c)
    if (scanf("%d %d", &r, &c) != 2) {
        return 0;
    }

    // Allocate memory for the matrix
    int **matrix = (int **)malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++) {
        matrix[i] = (int *)malloc(c * sizeof(int));
    }

    // Read the matrix elements
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Define boundaries
    int top = 0;
    int bottom = r - 1;
    int left = 0;
    int right = c - 1;
    
    int total_elements = r * c;
    int count = 0;

    // Traverse in spiral order
    while (top <= bottom && left <= right) {
        // 1. Traverse from Left to Right
        for (int i = left; i <= right; i++) {
            printf("%d", matrix[top][i]);
            if (++count < total_elements) printf(" ");
        }
        top++;

        // 2. Traverse from Top to Bottom
        for (int i = top; i <= bottom; i++) {
            printf("%d", matrix[i][right]);
            if (++count < total_elements) printf(" ");
        }
        right--;

        // 3. Traverse from Right to Left
        // Check if rows still remain to avoid duplicate traversal
        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                printf("%d", matrix[bottom][i]);
                if (++count < total_elements) printf(" ");
            }
            bottom--;
        }

        // 4. Traverse from Bottom to Top
        // Check if columns still remain to avoid duplicate traversal
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                printf("%d", matrix[i][left]);
                if (++count < total_elements) printf(" ");
            }
            left++;
        }
    }
    printf("\n");

    // Free allocated memory
    for (int i = 0; i < r; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}