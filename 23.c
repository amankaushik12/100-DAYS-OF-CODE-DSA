#include <stdio.h>
#include <stdlib.h>

// Definition of the Linked List Node
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Helper function to insert a node at the end of the list
void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    
    // If list is empty, make the new node the head
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    // Traverse to the end of the list
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    // Link the new node
    temp->next = newNode;
}

// Function to merge two sorted linked lists
struct Node* mergeSortedLists(struct Node* l1, struct Node* l2) {
    // Create a dummy node to act as the starting point
    // This simplifies the code by handling edge cases (empty lists) automatically
    struct Node dummy;
    struct Node* tail = &dummy;
    dummy.next = NULL;

    // Traverse both lists
    while (l1 != NULL && l2 != NULL) {
        if (l1->data <= l2->data) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // Attach the remaining elements of l1 or l2
    // (One of them is NULL at this point)
    if (l1 != NULL) {
        tail->next = l1;
    } else {
        tail->next = l2;
    }

    // Return the merged list (skipping the dummy node)
    return dummy.next;
}

// Function to print the linked list
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" ");
        }
        temp = temp->next;
    }
    printf("\n");
}

// Function to free allocated memory
void freeList(struct Node* head) {
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int n, m;
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;

    // --- Input for First List ---
    if (scanf("%d", &n) != 1) return 0;
    
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        insertEnd(&list1, val);
    }

    // --- Input for Second List ---
    if (scanf("%d", &m) != 1) return 0;

    for (int i = 0; i < m; i++) {
        int val;
        scanf("%d", &val);
        insertEnd(&list2, val);
    }

    // --- Merge Lists ---
    struct Node* mergedHead = mergeSortedLists(list1, list2);

    // --- Output ---
    printList(mergedHead);

    // --- Cleanup ---
    freeList(mergedHead);

    return 0;
}