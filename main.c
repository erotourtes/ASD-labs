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

  int rows = 6; 
  int colums = 6;

  for (short p = 0; p < 1; p++) {

    //to right
    for (short j = 0; j < colums; j++) {
      print(0, j);
    }

    //to down
    for (short i = 1; i < rows; i++) {
      print(i, colums - 1);
    }

    //to left
    for (short j = colums - 1 - 1; j > 0; j--) {
      print(rows - 1, j);
    }

    //to up
    for (short i = rows - 1; i > 0; i--) {
      print(i, 0);
    }

  }
  

	getch();
	endwin();	

  return 0;
}
