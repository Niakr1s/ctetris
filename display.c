#include "display.h"

WINDOW* newGlassWin() {
  int w = getmaxx(stdscr);
  int y = 2;
  int x = (w - GLASS_WIDTH) / 2;

  WINDOW* res = newwin(GLASS_HEIGHT, GLASS_WIDTH, y, x);
  return res;
}

void printGlass(WINDOW* win, Glass* glass) {
  wclear(win);
  for (int row = 0; row != GLASS_HEIGHT; ++row) {
    for (int col = 0; col != GLASS_WIDTH; ++col) {
      if (glass->cells[row][col] != 0) {
        mvwaddch(win, row, col, 'X');
      }
    }
  }
  if (glass->figure) {
    for (int i = 0; i != FIGURE_MAX_CELLS; ++i) {
      Pos abs_pos =
          posToAbsolutePos(glass->figure->cells[i], glass->figure->pos);
      mvwaddch(win, abs_pos.y, abs_pos.x, 'O');
    }
  }
  wmove(win, 0, 0);
  wrefresh(win);
}

void printFrame(WINDOW* win) {
  int h, w;
  getmaxyx(win, h, w);

  int y, x;
  getbegyx(win, y, x);

  for (int iy = y; iy != y + h; ++iy) {
    mvwaddch(stdscr, iy, x - 1, '|');
    mvwaddch(stdscr, iy, x + w, '|');
  }
  for (int ix = x - 1; ix != x + w + 1; ++ix) {
    mvwaddch(stdscr, y - 1, ix, '-');
    mvwaddch(stdscr, y + h, ix, '-');
  }
  refresh();
}

void initInput() {
  noecho();
  keypad(stdscr, TRUE);
  //  nodelay(stdscr, TRUE);
}

void gameLoop(WINDOW* win, Glass* glass) {
  initInput();
  printFrame(win);
  printGlass(win, glass);
  int count = 0;
  int ch;
  for (;;) {
    if ((ch = getch()) != ERR) {
      ++count;
      switch (ch) {
        case (KEY_RIGHT):
          glassFigureMoveX(glass, 1);
          break;
        case (KEY_LEFT):
          glassFigureMoveX(glass, -1);
          break;
        case (KEY_DOWN):
          glassFigureMoveY(glass, 1);
          break;
        case (KEY_UP):
          glassFigureMoveY(glass, -1);
          break;
        case ('r'):
          printGlass(win, glass);
          break;
        case (' '):
          rotateRight(glass->figure);
          break;
        case ('q'):
          return;
      }
      printGlass(win, glass);
      if (glass->figure) {
        move(0, 0);
        printw("%d, %d, %d", figureLeft(glass->figure),
               figureRight(glass->figure), figureBottom(glass->figure));
      }
    }
  }
}
