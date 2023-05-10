//
// Created by sirmax on 5/9/23.
//

#include "list.h"
#include <stdlib.h>

List *list_init() {
    List *l = (List *) malloc(sizeof(List));
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}

void list_add(List *l, void *value) {
    ListNode *node = (ListNode *) malloc(sizeof(ListNode));
    node->value = value;
    node->next = NULL;

    if (l->head == NULL)
        l->head = node;
    else
        l->tail->next = node;

    l->tail = node;
    l->size++;
}

void *list_remove(List *l, int index) {
    if (index < 0 || index >= l->size)
        return NULL;

    ListNode *current = l->head;
    ListNode *prev = NULL;
    for (int i = 0; i < index; i++) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) { // if remove first element
        l->head = current->next;
    }

    void *value = current->value;
    free(current);
    l->size--;
    return value;
}

void list_clear(List *l) {
    while (l->size > 0)
        free(list_remove(l, 0));
    free(l);
}