#ifndef INC_2_2_5_QUEUE_H
#define INC_2_2_5_QUEUE_H

typedef struct Node Node;
struct Node {
    void *val;
    Node *next;
};

typedef struct {
    Node *head;
    Node *tail;
    size_t size;
    size_t value_size;
} Queue;

Queue get_queue(size_t value_size);

void enqueue(Queue *queue, void *val);

void *dequeue(Queue *queue);

void *peek(Queue queue);

void free_queue(Queue *queue);

#endif //INC_2_2_5_QUEUE_H
