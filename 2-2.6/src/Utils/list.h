//
// Created by sirmax on 5/9/23.
//

#ifndef INC_2_2_5_LIST_H
#define INC_2_2_5_LIST_H

typedef struct ListNode ListNode;
struct ListNode {
    void *value;
    ListNode *next;
};

typedef struct {
    ListNode *head;
    ListNode *tail;
    int size;
} List;

List *list_init();

void list_add(List *l, void *value);

void *list_remove(List *l, int index);

void free_list(List *l);

void *list_get(List *l, int index);

#endif //INC_2_2_5_LIST_H
