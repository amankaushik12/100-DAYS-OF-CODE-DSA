#include <stdio.h>
#include <stdlib.h>

// Definition of a tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Helper function to allocate a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to find the index of a value in the inorder array
int search(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// Recursive function to construct the binary tree
struct Node* buildTree(int in[], int post[], int inStart, int inEnd, int* postIndex) {
    // Base case
    if (inStart > inEnd) {
        return NULL;
    }

    // Pick current node from Postorder traversal using postIndex and decrement postIndex
    struct Node* node = newNode(post[*postIndex]);
    (*postIndex)--;

    // If this node has no children, return it
    if (inStart == inEnd) {
        return node;
    }

    // Else find the index of this node in Inorder traversal
    int inIndex = search(in, inStart, inEnd, node->data);

    // Using index in Inorder traversal, construct right and left subtrees.
    // IMPORTANT: Build the right subtree first because we are traversing postorder backwards!
    node->right = buildTree(in, post, inIndex + 1, inEnd, postIndex);
    node->left = buildTree(in, post, inStart, inIndex - 1, postIndex);

    return node;
}

// Function to print the preorder traversal of the tree
void preOrder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->data);
    preOrder(node->left);
    preOrder(node->right);
}

int main() {
    int n;
    
    // Read the number of nodes
    if (scanf("%d", &n) != 1) return 1;

    int in[n], post[n];

    // Read inorder traversal
    for (int i = 0; i < n; i++) {
        scanf("%d", &in[i]);
    }

    // Read postorder traversal
    for (int i = 0; i < n; i++) {
        scanf("%d", &post[i]);
    }

    // Index for the postorder array (starts from the last element)
    int postIndex = n - 1;

    // Construct the tree
    struct Node* root = buildTree(in, post, 0, n - 1, &postIndex);

    // Print preorder traversal
    preOrder(root);
    printf("\n");

    return 0;
}