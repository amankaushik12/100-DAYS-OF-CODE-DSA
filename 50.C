#include <stdio.h>
#include <stdlib.h>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/* --- SOLUTION START --- */

struct TreeNode* searchBST(struct TreeNode* root, int val) {
    // Iterate as long as we haven't reached a null pointer
    while (root != NULL) {
        // Check if the current node is the target
        if (root->val == val) {
            return root;
        }
        
        // If target is smaller, go left. Otherwise, go right.
        if (val < root->val) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    
    // Return NULL if the value is not found
    return NULL;
}

/* --- SOLUTION END --- */


// ==================================================
// HELPER FUNCTIONS FOR TESTING IN VS CODE
// (These are used to build a tree and print results)
// ==================================================

// Helper function to create a new node
struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper function to print the tree (In-order traversal)
void printTree(struct TreeNode* root) {
    if (root == NULL) {
        printf("null ");
        return;
    }
    printf("%d ", root->val);
    printTree(root->left);
    printTree(root->right);
}

int main() {
    // Example 1: Construct the tree [4,2,7,1,3]
    struct TreeNode* root = createNode(4);
    root->left = createNode(2);
    root->right = createNode(7);
    root->left->left = createNode(1);
    root->left->right = createNode(3);

    int valToFind = 2;
    
    printf("Tree (Pre-order): ");
    printTree(root);
    printf("\nSearching for value: %d\n", valToFind);

    // Call the solution function
    struct TreeNode* result = searchBST(root, valToFind);

    if (result != NULL) {
        printf("Found Subtree (Pre-order): ");
        printTree(result);
        printf("\n");
    } else {
        printf("Value not found.\n");
    }

    // Example 2: Search for a value that doesn't exist (5)
    valToFind = 5;
    printf("\nSearching for value: %d\n", valToFind);
    result = searchBST(root, valToFind);
    
    if (result != NULL) {
        printTree(result);
    } else {
        printf("Value not found.\n");
    }

    return 0;
}