#include <stdio.h>

#define MAX_SIZE 1000

int stack[MAX_SIZE];
int top = -1;

// Function to push an element onto the stack
void push(int val) {
    if (top >= MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = val;
}

// Function to pop an element from the stack
void pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        return;
    }
    printf("%d\n", stack[top--]);
}

// Function to display elements from top to bottom
void display() {
    if (top == -1) {
        printf("\n");
        return;
    }
    for (int i = top; i >= 0; i--) {
        printf("%d", stack[i]);
        if (i > 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    int n, operation, value;

    // Read number of operations
    scanf("%d", &n);

    while (n--) {
        scanf("%d", &operation);

        if (operation == 1) {
            // Push operation
            scanf("%d", &value);
            push(value);
        } else if (operation == 2) {
            // Pop operation
            pop();
        } else if (operation == 3) {
            // Display operation
            display();
        }
    }

    return 0;
}