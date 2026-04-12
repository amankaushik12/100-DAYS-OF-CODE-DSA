#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int m, n;
    
    // Read table size and number of operations
    if (scanf("%d", &m) != 1) return 0;
    if (scanf("%d", &n) != 1) return 0;

    // Allocate memory for the hash table and initialize with -1 (assuming non-negative keys)
    int *table = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        table[i] = -1;
    }

    char op[15];
    int key;

    // Process each operation
    for (int step = 0; step < n; step++) {
        scanf("%s %d", op, &key);

        if (strcmp(op, "INSERT") == 0) {
            int i = 0;
            int h_k = key % m;
            
            // Probe using h(k, i) = (h(k) + i^2) % m
            while (i < m) {
                int idx = (h_k + i * i) % m;
                
                // Insert if the slot is empty or the key already exists (to avoid duplicates)
                if (table[idx] == -1 || table[idx] == key) {
                    table[idx] = key;
                    break;
                }
                i++;
            }
        } 
        else if (strcmp(op, "SEARCH") == 0) {
            int i = 0;
            int h_k = key % m;
            int found = 0;
            
            // Search using h(k, i) = (h(k) + i^2) % m
            while (i < m) {
                int idx = (h_k + i * i) % m;
                
                if (table[idx] == key) {
                    found = 1;
                    break;
                } 
                else if (table[idx] == -1) {
                    // Stop searching if an empty slot is encountered
                    break;
                }
                i++;
            }
            
            if (found) {
                printf("FOUND\n");
            } else {
                printf("NOT FOUND\n");
            }
        }
    }

    // Clean up allocated memory
    free(table);
    return 0;
}