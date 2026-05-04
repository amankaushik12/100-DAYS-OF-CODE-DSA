#include <stdio.h>
#include <stdlib.h>

struct Node {
    float val;
    struct Node* next;
};

void insertSorted(struct Node** head, float value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = value;
    newNode->next = NULL;

    if (*head == NULL || (*head)->val >= value) {
        newNode->next = *head;
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL && temp->next->val < value)
            temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void bucketSort(float arr[], int n) {
    struct Node** buckets = (struct Node**)malloc(n * sizeof(struct Node*));

    for (int i = 0; i < n; i++)
        buckets[i] = NULL;

    for (int i = 0; i < n; i++) {
        int idx = n * arr[i];
        insertSorted(&buckets[idx], arr[i]);
    }

    int k = 0;
    for (int i = 0; i < n; i++) {
        struct Node* temp = buckets[i];
        while (temp != NULL) {
            arr[k++] = temp->val;
            struct Node* del = temp;
            temp = temp->next;
            free(del);
        }
    }

    free(buckets);
}

int main() {
    float arr[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
    int n = sizeof(arr) / sizeof(arr[0]);

    bucketSort(arr, n);

    for (int i = 0; i < n; i++)
        printf("%.2f ", arr[i]);

    return 0;
}