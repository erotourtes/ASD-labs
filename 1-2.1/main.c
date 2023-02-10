#include <stdio.h>

int main (int argc, char *argv[]) {
  printf("Lab 2.1 \n");

  // float a[][3] = { {9, 9, 6}, {9, 6, 2}, {6, 6, 2}, {-1, 3, 2}, {-1, 3, 1}, {-10, 2, 0}, };

  // float a[][3] = { {9, 9, 6}, {9, 6, 2}, {9, 6, 2}, {8, 3, 2}, {8, 3, 1}, {8, 2, 0}, {5, 2, 0}, {5, 2, 0}, {5, 2, 0}, }; 

  // float a[][3] = { {8, 6, 7}, {8, 6, 7}, {8, 6, 7}, {6, -1, 6}, {6, -1, 0}, {6, -1, 0}, };

  // float a[][4] = { {9, 9, 20, 6}, {9, 6, 20, 5}, {6, 6,  15, 4}, {-1, -1, 15, 3}, {-1, -2, 10, 2}, {-10, -2, 10, 1}, };

  float a[][4] = { {9, 9, 20, 7}, {9, 6, 20, 7}, {6, 6,  15, 7}, {-1, -1, 15, 7}, {-1, -2, 10, 7}, {-10, -2, 10, -1}, };

  const int m = (int)(sizeof(a) / sizeof(a[0]));
  const int n = (int)(sizeof(a[0]) / sizeof(a[0][0]));
  printf("m = %i, n = %i \n", m, n);

  printf("Printing the matrix\n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%*.1f ", 5, a[i][j]);
    }
    printf("\n");
  }

  for (int j = 0; j < n; j++) {
    int up = 0;
    int down = m - 1; 
    while (up <= down) {
      int mid = (up + down) / 2;
      float val = a[mid][j];
      // printf("a[%i, %i] = %f \n", mid, j, val);

      if (0 <= val && val <= 5) {
        printf("Found! a[%i, %i] = %f", mid, j, val);
        return 0;
      } else if(val > 5) {
        up = mid + 1;
      } else if(val < 0) {
        down = mid - 1;
      }
    }
  }

  printf("There is no such element");

  return 0;
}
