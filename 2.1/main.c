#include <stdio.h>

int main (int argc, char *argv[]) {
  printf("Lab 2.1 \n");

  // float a[][3] = {
  //   {10,  9, 6},
  //   {10,  6, 2},
  //   {6,   6, 2},
  //   {-1,  3, 2},
  //   {-1,  3, 1},
  //   {-10, 2, 0},
  // };

  float a[][3] = {
    {10,  9, 1},
    {10,  6, -1},
    {6,   6, -1},
    {-1,  6, -1},
    {-1,  6, -1},
    {-10, 6, -1},
  };

  const int m = (int)(sizeof(a) / sizeof(a[0]));
  const int n = (int)(sizeof(a[0]) / sizeof(a[0][0]));
  printf("m = %i, n = %i \n", m, n);

  printf("Printing the matrix\n");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      printf("%.1f ", a[i][j]);
    }
    printf("\n");
  }

  for (int j = 0; j < n; j++) {
    int up = 0;
    int down = m - 1; 
    while (up <= down) {
      int mid = (up + down) / 2;
      float val = a[mid][j];
      printf("a[%i, %i] = %f \n", mid, j, val);

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
