#include <malloc.h>
#include <stdlib.h>
#include "queue.h"

Queue get_queue() {
    return (Queue) {NULL, NULL, 0};
}

void enqueue(Queue *queue, int val) {
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

int dequeue(Queue *queue) {
    if (queue->head == NULL) {
        printf("Queue is empty!");
        exit(1);
    };

    Node *node = queue->head;
    queue->head = queue->head->next;
    int val = node->val;
    free(node);
    queue->size--;
    return val;
}

void free_queue(Queue *queue) {
    while (queue->head != NULL) {
        Node *node = queue->head;
        queue->head = queue->head->next;
        free(node);
    }
}

int peek(Queue queue) {
    if (queue.head == NULL) {
        printf("Queue is empty!");
        exit(1);
    };

    return queue.head->val;
}