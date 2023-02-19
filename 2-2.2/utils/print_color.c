#include <stdio.h>

void set_urgent_color() {
  printf("\033[41;30m");
}

void set_info_color() {
  printf("\033[44;30m");
}

void reset_color() {
  printf("\033[0m");
}

