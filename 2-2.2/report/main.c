#include "List.c"

int main() {
  int n = 0;
  scanf("%d", &n);

  List *s1 = init_list();
  List *s2 = init_list();

  for (int i = 0; i < n * 2; i++)
      add_value(s1, (i + 1) * 10);

  for (int i = 0; i < n; i++)
      add_value(s2, i + 1);

  print_list(s1);
  print_list(s2);

  printf("\nAfter combining\n\n");

  List *list = combine_lists_center(&s1, &s2);

  // s1 and s2 now null to avoid memory leaks
  print_list(s1);
  print_list(s2);
  print_list(list);

    free_list(list);

  // free_list(s1);
  // free_list(s2);
  return 0;
}
