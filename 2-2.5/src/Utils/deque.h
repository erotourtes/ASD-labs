#ifndef INC_2_2_5_DEQUE_H
#define INC_2_2_5_DEQUE_H

typedef struct Node Node;
struct Node {
    void *val;
    Node *next;
    Node *prev;
};

typedef struct {
    Node *head;
    Node *tail;
    size_t size;
    size_t value_size;
} Deque;

Deque get_deque(size_t value_size);

void enqueue(Deque *deque, void *val);

void* pop(Deque *deque);

void push(Deque *deque, void *val);

void *dequeue(Deque *deque);

void *peek(Deque deque);

void free_deque(Deque *deque);

#endif //INC_2_2_5_DEQUE_H
