#include <stdio.h>

void printMatrix(int n, int[][n]);

int main() {
  printf("Lab 2.2\n");


  // int a[][7] = {{1, 2, 3, 4, 4, 6, 7}, {1, 2, 3, 4, 4, 6, 7}, {1, 2, 3, 4, 4, 6, 7}, {1, 2, 3, 4, 4, 6, 7}, {1, 2, 3, 4, 4, 6, 7}, {1, 2, 3, 4, 4, 6, 7}, {1, 2, 3, 4, 4, 6, 7}};

  // int a[][7] = {{3, 8, 8, 5, 2, 6, 1}, {0, 0, 5, 2, 2, 5, 4}, {9, 4, 4, 5, 6, 8, 4}, {7, 8, 3, 8, 4, 9, 3}, {8, 5, 5, 7, 8, 3, 5}, {0, 2, 5, 0, 0, 6, 5}, {7, 7, 2, 7, 7, 5, 7} };

  int a[][7] = {{7, 6, 4, 4, 3, 2, 1}, {7, 6, 4, 4, 3, 2, 1}, {7, 6, 4, 4, 3, 2, 1}, {7, 6, 4, 4, 3, 2, 1}, {7, 6, 4, 4, 3, 2, 1}, {7, 6, 4, 4, 3, 2, 1}, {7, 6, 4, 4, 3, 2, 1}, };


  int n = sizeof(a) / sizeof(a[0]);
  printMatrix(n, a);

  for (int i = 1; i < n; i++) {
    int j = i;
    int temp = a[j][j];
    while (temp < a[j-1][j-1] && j > 0) {
      a[j][j] = a[j-1][j-1];
      j--;
    }
    a[j][j] = temp;
  }

  printf("Sorted:\n");
  printMatrix(n, a);

  return 0;
}

void printMatrix(int n, int a[][n]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      printf("%*d ", 1, a[i][j]);
    printf("\n");
  }
}
