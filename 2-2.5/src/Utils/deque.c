#include <malloc.h>
#include <stdlib.h>
#include "deque.h"

Deque get_deque(size_t value_size) {
    return (Deque) {NULL, NULL, 0, value_size};
}

void enqueue(Deque *deque, void *val) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;
    node->prev = deque->tail;

    if (deque->head == NULL) {
        deque->head = node;
        deque->tail = deque->head;
    } else {
        deque->tail->next = node;
        deque->tail = node;
    }

    deque->size++;
}

void *dequeue(Deque *deque) {
    if (deque->head == NULL) {
        printf("Deque is empty!");
        exit(1);
    };

    Node *node = deque->head;
    deque->head = deque->head->next;
    void* val = node->val;
    free(node);
    deque->size--;
    return val;
}

void push(Deque *deque, void *val) {
    enqueue(deque, val);
}

void* pop(Deque *deque) {
    if (deque->head == NULL) {
        printf("Deque is empty!");
        exit(1);
    }

    Node *node = deque->tail;
    if (deque->tail == deque->head) deque->head = NULL;
    deque->tail = deque->tail->prev;
    void* val = node->val;
    free(node);
    deque->size--;
    return val;
}

void free_deque(Deque *deque) {
    while (deque->head != NULL) {
        Node *node = deque->head;
        deque->head = deque->head->next;
        free(node->val);
        free(node);
    }

    deque->tail = NULL;
    deque->size = 0;
}