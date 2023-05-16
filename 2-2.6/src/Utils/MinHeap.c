//
// Created by sirmax on 5/12/23.
//

#include <malloc.h>
#include "MinHeap.h"

void swap(MinHeap *heap, int a, int b);

void babble_up(MinHeap *heap, int child_index);

void babble_down(MinHeap *heap, int parent);

MinHeap heap_init(int capacity) {
    HeapNode *values = calloc(capacity, sizeof(HeapNode));

    return (MinHeap) {values, 0, .capacity=capacity};
}

void heap_add(MinHeap *heap, void *value, int weight) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->values = realloc(heap->values, heap->capacity * sizeof(void *));
    }

    heap->values[heap->size++] = (HeapNode) {.value=value, weight};
    babble_up(heap, heap->size - 1);
}

HeapNode heap_remove_min(MinHeap *heap) {
    HeapNode min = heap->values[0];
    heap->values[0] = heap->values[--heap->size];

    babble_down(heap, 0);

    return min;
}

void heap_update_if_less(MinHeap *heap, void *value, int weight) {
    int i;
    for (i = 0; i < heap->size; ++i)
        if (heap->values[i].value== value)
            break;

    if (i == heap->size) return;
    if (heap->values[i].weight <= weight) return;

    heap->values[i].weight = weight;
    babble_up(heap, i);
    babble_down(heap, i);
}

void heap_free_heap_only(MinHeap *heap) {
    free(heap->values);
    heap->values = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

void babble_down(MinHeap *heap, int parent) {
    int left_child_index = parent * 2 + 1;
    if (left_child_index > heap->size) return;

    int right_child_index = parent * 2 + 2;
    right_child_index = right_child_index >= heap->size ? left_child_index : right_child_index;

    HeapNode left_child = heap->values[left_child_index];
    HeapNode right_child = heap->values[right_child_index];

    if (left_child.weight > heap->values[parent].weight && right_child.weight > heap->values[parent].weight) return;

    int min_child = left_child_index;
    if (left_child.weight > right_child.weight) min_child = right_child_index;

    swap(heap, min_child, parent);

    babble_down(heap, min_child);
}


void babble_up(MinHeap *heap, int child_index) {
    if (child_index == 0)
        return;

    int parent_index = (child_index - 1) / 2;

    HeapNode parent_value = heap->values[parent_index];
    HeapNode child_value = heap->values[child_index];
    if (parent_value.weight < child_value.weight) return;
    swap(heap, parent_index, child_index);

    babble_up(heap, parent_index);
}

void swap(MinHeap *heap, int a, int b) {
    HeapNode tmp = heap->values[a];
    heap->values[a] = heap->values[b];
    heap->values[b] = tmp;
}