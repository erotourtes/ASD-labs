#ifndef INC_2_2_5_QUEUE_H
#define INC_2_2_5_QUEUE_H

typedef struct Node Node;
struct Node {
    int val;
    Node *next;
};

typedef struct {
    Node *head;
    Node *tail;
    int size;
} Queue;

Queue get_queue();

void enqueue(Queue *queue, int val);

int dequeue(Queue *queue);

int peek(Queue queue);

void free_queue(Queue *queue);

#endif //INC_2_2_5_QUEUE_H
