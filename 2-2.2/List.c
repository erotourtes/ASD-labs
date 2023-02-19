#include "./utils/print_color.c"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
  unsigned int value;
  struct Node *next;
} Node;

typedef struct List {
  Node *head;
  Node *tail;
  int size;
} List;

List *initList() {
  List *list = malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

void addNode(List *list, int value) {
  if (value < 0) {
    fprintf(stderr, "Error: negative value not allowed\n");
    return;
  }

  Node *node = (Node *)malloc(sizeof(Node));
  node->value = value;
  node->next = NULL;

  if (list->head == NULL) {
    list->head = node;
    list->tail = list->head;
  } else {
    list->tail->next = node;
    list->tail = list->tail->next;
  }

  list->size++;
}

void print_list(List *list) {
  set_info_color();
  if (list != NULL && list->head != NULL) {
    Node *current = list->head;

    reset_color();
    printf("\nHead: %d\n", list->head->value);
    printf("Tail: %d\n", list->tail->value);
    set_info_color();

    printf("%d: ", list->size);

    while (current != NULL) {
      printf("%d-> ", current->value);
      current = current->next;
    }
  }

  printf("NULL\n");
  reset_color();
}

void freeList(List *list) {
  Node *current = list->head;
  Node *next = NULL;

  set_urgent_color();
  printf("Freeing: ");

  while (current != NULL) {
    printf("%d ", current->value);
    next = current->next;
    free(current);
    current = next;
  }

  reset_color();
  printf("\n");
}

// Combines two lists into one list, where the second list is inserted in the
// middle of the first list; both pointers would be null, return pointer to a
// new list;
List *combine_lists_center(List **list1ptr, List **list2ptr) {
  List *list1 = *list1ptr;
  List *list2 = *list2ptr;

  Node *slow = list1->head;
  Node *fast = list1->head;

  while (fast != NULL && fast->next != NULL) {
    fast = fast->next->next;

    if (fast != NULL)
      slow = slow->next;
  }


  // slow will be in the middle of the list
  Node *tmp = slow->next;
  slow->next = list2->head;
  list2->tail->next = tmp;

  list1->size += list2->size;

  List *newList = list1;
  free(list2);
  *list2ptr = NULL;
  *list1ptr = NULL;

  return newList;
}
