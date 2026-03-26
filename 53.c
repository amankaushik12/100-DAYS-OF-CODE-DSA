#include <stdio.h>
#include <stdlib.h>

// Tree Node
struct Node {
    int data;
    struct Node *left, *right;
};

// Queue for level order traversal
struct QNode {
    struct Node* node;
    int hd;
};

struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Create tree from level order input
struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    struct Node* root = newNode(arr[0]);

    struct Node* queue[n];
    int front = 0, rear = 0;

    queue[rear++] = root;
    int i = 1;

    while (i < n) {
        struct Node* current = queue[front++];

        // Left child
        if (arr[i] != -1) {
            current->left = newNode(arr[i]);
            queue[rear++] = current->left;
        }
        i++;

        if (i >= n) break;

        // Right child
        if (arr[i] != -1) {
            current->right = newNode(arr[i]);
            queue[rear++] = current->right;
        }
        i++;
    }

    return root;
}

// Structure to store vertical nodes
struct List {
    int data[100];
    int size;
};

// Vertical Order Traversal
void verticalOrder(struct Node* root) {
    if (!root) return;

    struct QNode queue[100];
    int front = 0, rear = 0;

    struct List map[200];  // For HD range
    for (int i = 0; i < 200; i++)
        map[i].size = 0;

    int offset = 100; // To handle negative HD

    // Push root
    queue[rear++] = (struct QNode){root, 0};

    int min = 0, max = 0;

    while (front < rear) {
        struct QNode temp = queue[front++];
        struct Node* node = temp.node;
        int hd = temp.hd;

        // Store node data
        map[hd + offset].data[map[hd + offset].size++] = node->data;

        if (hd < min) min = hd;
        if (hd > max) max = hd;

        // Left child
        if (node->left)
            queue[rear++] = (struct QNode){node->left, hd - 1};

        // Right child
        if (node->right)
            queue[rear++] = (struct QNode){node->right, hd + 1};
    }

    // Print result
    for (int i = min; i <= max; i++) {
        for (int j = 0; j < map[i + offset].size; j++) {
            printf("%d ", map[i + offset].data[j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    struct Node* root = buildTree(arr, n);

    verticalOrder(root);

    return 0;
}