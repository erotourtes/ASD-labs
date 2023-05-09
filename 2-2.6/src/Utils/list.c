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

    if (l->head == NULL) {
        l->head = node;
        l->tail = node;
    } else {
        l->tail->next = node;
        l->tail = node;
    }

    l->size++;
}

void *list_remove(List *l, int index) {
    if (index < 0 || index >= l->size)
        return NULL;

    ListNode *current = l->head;
    for (int i = 0; i < index - 1; i++)
        current = current->next;

    ListNode *to_remove = current->next;
    current->next = to_remove->next;

    void *value = to_remove->value;
    free(to_remove->next);
    free(to_remove);
    l->size--;
    return value;
}

void list_clear(List *l) {
    while (l->size > 0)
        free(list_remove(l, 0));
}