#include <malloc.h>
#include <stdlib.h>
#include "queue.h"

Queue get_queue(size_t value_size) {
    return (Queue) {NULL, NULL, 0, value_size};
}

void enqueue(Queue *queue, void *val) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = NULL;

    if (queue->head == NULL) {
        queue->head = node;
        queue->tail = queue->head;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }

    queue->size++;
}

void *dequeue(Queue *queue) {
    if (queue->head == NULL) {
        printf("Queue is empty!");
        exit(1);
    };

    Node *node = queue->head;
    queue->head = queue->head->next;
    void* val = node->val;
    free(node);
    queue->size--;
    return val;
}

void free_queue(Queue *queue) {
    while (queue->head != NULL) {
        Node *node = queue->head;
        queue->head = queue->head->next;
        free(node->val);
        free(node);
    }

    queue->tail = NULL;
    queue->size = 0;
}

void *peek(Queue queue) {
    if (queue.head == NULL) {
        printf("Queue is empty!");
        exit(1);
    };

    return queue.head->val;
}