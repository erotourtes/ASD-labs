#include <ncurses.h>

void print(short i, short j) {
      mvprintw(i, j, "%i", 1);

      refresh();
      napms(350);
}

int main (int argc, char *argv[])
{
  initscr();

	printw("Lab 1.6");	
  refresh();
  napms(1000);
  clear();

  // int rows = 25; 
  // int colums = 80;

  int rows = 5; 
  int colums = 7;

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
    for (short j = numOfCircles; j < colums - numOfCircles + p; j++) {
      print(numOfCircles - p, j);
    }

    //to down
    for (short i = numOfCircles + 1 - p; i < numOfCircles + 2 + p; i++) {
      print(i, colums - numOfCircles + p - 1);
    }

    //to left
    for (short j = colums - numOfCircles - 2 + p; j > numOfCircles - 2 - p; j--) {
      print(numOfCircles + 1 + p, j);
    }

    //to up
    for (short i = numOfCircles + p; i > numOfCircles - 2 - p; i--) {
      print(i, numOfCircles - 1 - p);
    }

  }
  

	getch();
	endwin();	

  return 0;
}
