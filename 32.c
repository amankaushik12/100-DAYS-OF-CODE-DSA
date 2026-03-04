#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int top;
    int capacity;
} Stack;

// Initialize the stack with a specific capacity
Stack* createStack(int capacity) {
    Stack *s = (Stack*)malloc(sizeof(Stack));
    s->arr = (int*)malloc(capacity * sizeof(int));
    s->top = -1;
    s->capacity = capacity;
    return s;
}

// Push an element onto the stack
void push(Stack *s, int val) {
    if (s->top < s->capacity - 1) {
        s->arr[++(s->top)] = val;
    }
}

// Pop an element from the stack
void pop(Stack *s) {
    if (s->top >= 0) {
        (s->top)--;
    }
}

int main() {
    int n, m, val;

    // 1. Read number of elements to push
    scanf("%d", &n);

    // Create stack based on input size
    Stack *stack = createStack(n);

    // 2. Push elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        push(stack, val);
    }

    // 3. Read number of elements to pop
    scanf("%d", &m);

    // Perform pop operations
    for (int i = 0; i < m; i++) {
        pop(stack);
    }

    // 4. Print remaining elements from top to bottom
    for (int i = stack->top; i >= 0; i--) {
        printf("%d", stack->arr[i]);
        if (i > 0) printf(" ");
    }
    printf("\n");

    // Clean up memory
    free(stack->arr);
    free(stack);

    return 0;
}