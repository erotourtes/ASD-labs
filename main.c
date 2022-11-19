#include <ncurses.h>

int main (int argc, char *argv[])
{
  initscr();

	printw("Lab 1.6");	
  refresh();
  napms(1000);
  clear();

  int rows = 25; 
  int colums = 80;
  
  for (short i = 0; i < rows; i++) {
    for (short j = 0; j < colums; j++) {
      mvprintw(i, j, "%i", 1);

      refresh();
      napms(3);
    }
  }

	getch();
	endwin();	

  return 0;
}
