#include <stdio.h>
int main() {
    int p, q;
    scanf("%d", &p);
    int a[p];
    for (int i = 0; i < p; i++) {      // Input for server log 1
        scanf("%d", &a[i]);
    }
    scanf("%d", &q);
    int b[q];
    for (int i = 0; i < q; i++) {     // Input for server log 2
        scanf("%d", &b[i]);
    }
    int i = 0, j = 0;
    while (i < p && j < q) {
        if (a[i] <= b[j]) {
            printf("%d ", a[i]);     // Merge both logs
            i++;
        } else {
            printf("%d ", b[j]);
            j++;
        }
    }   
    while (i < p) {
        printf("%d ", a[i]);        // Print remaining elements of log 1
        i++;
    }
    while (j < q) {
        printf("%d ", b[j]);    // Print remaining elements of log 2
        j++;
    }

    return 0;
}
