//
// Created by sirmax on 5/12/23.
//

#ifndef INC_2_2_6_MINHEAP_H
#define INC_2_2_6_MINHEAP_H

typedef struct MinHeap MinHeap;

struct MinHeap {
    void **values;

    int (*compare)(void *a, void *b);

    int size;
    int capacity;
};

MinHeap heap_init(int (*compare)(void *a, void *b));

void heap_add(MinHeap *heap, void *value);

void *heap_remove_min(MinHeap *heap);

void heap_free_heap_only(MinHeap *heap);

#endif //INC_2_2_6_MINHEAP_H
