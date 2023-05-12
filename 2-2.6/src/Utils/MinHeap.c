//
// Created by sirmax on 5/12/23.
//

#include <malloc.h>
#include "MinHeap.h"

void swap(MinHeap *heap, int a, int b);

void babble_up(MinHeap *heap, int child_index);

void babble_down(MinHeap *heap, int parent);

MinHeap heap_init(int (*compare)(void *a, void *b)) {
    int capacity = 10;
    void *values = calloc(capacity, sizeof(void *));

    return (MinHeap) {values, compare, 0, capacity};
}

void heap_add(MinHeap *heap, void *value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->values = realloc(heap->values, heap->capacity * sizeof(void *));
    }

    heap->values[heap->size++] = value;
    babble_up(heap, heap->size - 1);
}

void *heap_remove_min(MinHeap *heap) {
    void *min = heap->values[0];
    heap->values[0] = heap->values[--heap->size];

    babble_down(heap, 0);

    return min;
}

void heap_free_heap_only(MinHeap *heap) {
    free(heap->values);
    heap->values = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

void babble_down(MinHeap *heap, int parent) {
    int left_child = parent * 2 + 1;
    if (left_child > heap->size) return;

    int right_child = parent * 2 + 2;
    right_child = right_child >= heap->size ? left_child : right_child;

    void *left_child_value = heap->values[left_child];
    void *right_child_value = heap->values[right_child];

    int min_child = left_child;
    if (heap->compare(left_child_value, right_child_value) > 0) min_child = right_child;

    swap(heap, min_child, parent);

    babble_down(heap, min_child);
}


void babble_up(MinHeap *heap, int child_index) {
    if (child_index == 0)
        return;

    int parent_index = (child_index - 1) / 2;

    void* parent_value = heap->values[parent_index];
    void* child_value = heap->values[child_index];
    if (heap->compare(parent_value, child_value) > 0) return;
    swap(heap, parent_index, child_index);

    babble_up(heap, parent_index);
}

void swap(MinHeap *heap, int a, int b) {
    void *tmp = heap->values[a];
    heap->values[a] = heap->values[b];
    heap->values[b] = tmp;
}