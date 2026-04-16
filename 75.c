#include <stdio.h>
#include <stdlib.h>

// --- Custom Hash Table Implementation ---
#define HASH_SIZE 10007 // A prime number for the hash table size

// Node structure for Separate Chaining in Hash Map
typedef struct Node {
    int key;       // The prefix sum
    int value;     // The earliest index where this sum was seen
    struct Node* next;
} Node;

// Array of pointers to Nodes
Node* hashTable[HASH_SIZE];

// Helper function to get a valid hash index (handles negative prefix sums)
int getHashIndex(int key) {
    int index = key % HASH_SIZE;
    if (index < 0) {
        index += HASH_SIZE;
    }
    return index;
}

// Function to insert a key-value pair into the hash table
void insert(int key, int value) {
    int index = getHashIndex(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Function to find a key in the hash table. 
// Returns the index if found, -1 otherwise.
int search(int key) {
    int index = getHashIndex(key);
    Node* temp = hashTable[index];
    while (temp != NULL) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }
    return -1;
}

// --- Main Algorithm ---
int maxLen(int arr[], int n) {
    int max_len = 0;
    int current_sum = 0;

    // Initialize hash table to NULL
    for(int i = 0; i < HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }

    for (int i = 0; i < n; i++) {
        current_sum += arr[i];

        // Case 1: The subarray starting from index 0 has a sum equal to 0
        if (current_sum == 0) {
            max_len = i + 1;
        }

        // Case 2: We have seen this prefix sum before
        int prev_index = search(current_sum);
        if (prev_index != -1) {
            int current_len = i - prev_index;
            if (current_len > max_len) {
                max_len = current_len;
            }
        } else {
            // Only insert if it's the FIRST time we see this sum.
            // This ensures we always get the maximum possible length.
            insert(current_sum, i);
        }
    }
    
    return max_len;
}

int main() {
    // Sample Input
    int arr[] = {15, -2, 2, -8, 1, 7, 10, 23};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    // Function Call
    int result = maxLen(arr, n);
    
    // Output
    printf("%d\n", result);
    
    return 0;
}