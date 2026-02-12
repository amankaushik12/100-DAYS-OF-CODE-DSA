#include <stdio.h>

#define MAX_SIZE 100

int main() {
    int matrix[MAX_SIZE][MAX_SIZE];
    int m, n;
    int isSymmetric = 1;

   
    scanf("%d %d", &m, &n);

    
    if (m != n) {
        printf("Not a Symmetric Matrix\n");
        return 0;
    }

  
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

  
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                isSymmetric = 0;
                break;
            }
        }
       
        if (!isSymmetric) {
            break;
        }
    }

   
    if (isSymmetric) {
        printf("Symmetric Matrix\n");
    } else {
        printf("Not a Symmetric Matrix\n");
    }

    return 0;
}