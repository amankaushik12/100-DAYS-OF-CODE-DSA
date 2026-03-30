#include <stdio.h>
#include <stdlib.h>

// Definition of a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new tree node
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
struct Node* buildTree(int in[], int pre[], int inStrt, int inEnd, int* preIndex) {
    // Base case: if start index is greater than end index, return NULL
    if (inStrt > inEnd) {
        return NULL;
    }

    // Pick current node from Preorder traversal using preIndex and increment preIndex
    struct Node* tNode = newNode(pre[*preIndex]);
    (*preIndex)++;

    // If this node has no children, return it immediately
    if (inStrt == inEnd) {
        return tNode;
    }

    // Else find the index of this node in the Inorder traversal
    int inIndex = search(in, inStrt, inEnd, tNode->data);

    // Using the index in Inorder traversal, construct left and right subtrees
    tNode->left = buildTree(in, pre, inStrt, inIndex - 1, preIndex);
    tNode->right = buildTree(in, pre, inIndex + 1, inEnd, preIndex);

    return tNode;
}

// Function to print postorder traversal of the tree
void printPostorder(struct Node* node) {
    if (node == NULL) {
        return;
    }
    // First recur on left subtree
    printPostorder(node->left);
    // Then recur on right subtree
    printPostorder(node->right);
    // Now deal with the node
    printf("%d ", node->data);
}

int main() {
    int n;
    
    // Read the number of nodes
    if (scanf("%d", &n) != 1) return 1;

    // Allocate arrays for preorder and inorder traversals
    int *pre = (int*)malloc(n * sizeof(int));
    int *in = (int*)malloc(n * sizeof(int));

    // Read preorder traversal
    for (int i = 0; i < n; i++) {
        scanf("%d", &pre[i]);
    }

    // Read inorder traversal
    for (int i = 0; i < n; i++) {
        scanf("%d", &in[i]);
    }

    // preIndex needs to be passed by reference so it increments across recursive calls
    int preIndex = 0;
    
    // Construct the tree
    struct Node* root = buildTree(in, pre, 0, n - 1, &preIndex);

    // Print the postorder traversal
    printPostorder(root);
    printf("\n");

    // Free allocated memory
    free(pre);
    free(in);

    return 0;
}
