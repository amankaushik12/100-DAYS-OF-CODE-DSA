#include <stdio.h>
#include <stdlib.h>

// structure of node
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// create new node
struct node* create(int data) {
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

// function to find height
int height(struct node* root) {
    if (root == NULL)
        return 0;

    int left = height(root->left);
    int right = height(root->right);

    if (left > right)
        return left + 1;
    else
        return right + 1;
}

int main() {
    // creating tree manually
    struct node* root = create(1);
    root->left = create(2);
    root->right = create(3);
    root->left->left = create(4);
    root->left->right = create(5);

    int h = height(root);

    printf("Height of tree = %d", h);

    return 0;
}