#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Structure for a stack node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Structure for the Stack, holding the top pointer
typedef struct Stack {
    Node* top;
} Stack;

// Function to initialize the stack
void initStack(Stack* s) {
    s->top = NULL;
}

// Function to check if stack is empty
int isEmpty(Stack* s) {
    return s->top == NULL;
}

// Function to push an element onto the stack (Dynamic Memory Allocation)
void push(Stack* s, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

// Function to pop an element from the stack
int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack Underflow: Invalid Postfix Expression.\n");
        exit(1);
    }
    Node* temp = s->top;
    int value = temp->data;
    s->top = s->top->next;
    free(temp); // Freeing dynamic memory
    return value;
}

// Helper function to perform arithmetic operations
int performOperation(char op, int a, int b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: 
            printf("Invalid operator encountered: %c\n", op);
            return 0;
    }
}

// Function to evaluate the postfix expression
int evaluatePostfix(char* expression) {
    Stack s;
    initStack(&s);

    // Iterate through the expression
    for (int i = 0; expression[i] != '\0'; i++) {
        // Skip whitespace
        if (expression[i] == ' ') {
            continue;
        }

        // If the character is a digit, parse the full number
        if (isdigit(expression[i])) {
            int num = 0;
            // Handle multi-digit numbers
            while (isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--; // Backtrack one step because the loop increments it
            push(&s, num);
        } 
        // If it is an operator, pop two operands and perform the operation
        else {
            int val1 = pop(&s); // Top operand
            int val2 = pop(&s); // Second top operand
            
            // Note: In stack val1 was pushed last. 
            // For subtraction/division: val2 (op) val1
            int result = performOperation(expression[i], val2, val1);
            push(&s, result);
        }
    }

    // The final result is the only element left in the stack
    return pop(&s);
}

int main() {
    // Example input: "2 3 1 * + 9 -"
    // Note: In a real scenario, you might read this using fgets or scanf
    char expression[] = "2 3 1 * + 9 -";

    printf("Input: %s\n", expression);
    
    int result = evaluatePostfix(expression);
    
    printf("Output: %d\n", result);

    return 0;
}