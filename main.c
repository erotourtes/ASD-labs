#include <ncurses.h>

void print(short i, short j, short color) {
      attron(COLOR_PAIR(color));

      mvprintw(i, j, "%i", 1);

      attroff(COLOR_PAIR(color));

      refresh();
      napms(350);
}

int main (int argc, char *argv[])
{
  initscr();

  start_color();
  init_pair(1, COLOR_BLACK, COLOR_BLUE);
  init_pair(2, COLOR_BLACK, COLOR_GREEN);
  init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(3, COLOR_BLACK, COLOR_YELLOW);

	printw("Lab 1.6");	
  refresh();
  napms(1000);
  clear();

  // int rows = 25; 
  // int colums = 80;

  int rows = 7; 
  int colums = 9;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < colums; j++) {
      mvprintw(i, j, "%i", 0);
    }
  }
  refresh();

  short numOfCircles = rows / 2;

  for (short p = 0; p < numOfCircles + 1; p++) {
    mvprintw(10, 10, "%i", p);

    //to right
    for (short j = numOfCircles - p; j < colums - numOfCircles + p; j++) {
      print(numOfCircles- p, j, 1);
    }

    //to down
    for (short i = numOfCircles + 1 - p; i < numOfCircles + 1 + p; i++) {
      print(i, colums - numOfCircles + p - 1, 2);
    }

    if (numOfCircles + 1 + p >= rows) break;
    //to left
    for (short j = colums - numOfCircles - 1 + p; j > numOfCircles - 2 - p; j--) {
      print(numOfCircles + 1 + p, j, 3);
    }

    //to up
    for (short i = numOfCircles + p; i > numOfCircles - 1 - p; i--) {
      print(i, numOfCircles - 1 - p, 4);
    }

  }
  

	getch();
	endwin();	

  return 0;
}
