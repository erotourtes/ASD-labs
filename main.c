#include <ncurses.h>

void init(void); 
void fillField(int, int);
void print(short, short, short);

int main (int argc, char *argv[])
{
  init();

  int rows = 3; 
  int colums = 15;

  if (rows > colums) {
    printw("To work properly colums should be GREATER than rows");	
    refresh();
    getch();
    clear();
  }

  fillField(rows, colums);

  short numOfCircles = rows / 2;
  if (rows % 2 == 0)
    numOfCircles--;

  for (short p = 0; p < numOfCircles + 1; p++) {

    //to right
    for (short j = numOfCircles - p; j < colums - numOfCircles + p; j++) {
      print(numOfCircles - p, j, 1);
    }

    //to down
    for (short i = numOfCircles + 1 - p; i < numOfCircles + 1 + p; i++) {
      print(i, colums - numOfCircles + p - 1, 2);
    }

    if (numOfCircles + 1 + p >= rows) break;

    //to left
    for (short j = colums - numOfCircles + p - 1; j > numOfCircles - 2 - p; j--) {
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

void init() {
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
}

void fillField(int rows, int colums) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < colums; j++) {
      mvprintw(i, j, "%i", 0);
    }
  }
  refresh();
}

void print(short i, short j, short color) {
      attron(COLOR_PAIR(color));
      mvprintw(i, j, "%i", 1);
      attroff(COLOR_PAIR(color));

      refresh();
      napms(350);
}
