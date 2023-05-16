//
// Created by sirmax on 5/12/23.
//

#ifndef INC_2_2_6_MINHEAP_H
#define INC_2_2_6_MINHEAP_H

typedef struct MinHeap MinHeap;

typedef struct {
    void *value;
    int weight;
} HeapNode;

struct MinHeap {
    HeapNode *values;

    int size;
    int capacity;
};

MinHeap heap_init(int capacity);

void heap_add(MinHeap *heap, void *value, int weight);

HeapNode heap_remove_min(MinHeap *heap);

void heap_free_heap_only(MinHeap *heap);

void heap_update_if_less(MinHeap *heap, void *value, int weight);

#endif //INC_2_2_6_MINHEAP_H
