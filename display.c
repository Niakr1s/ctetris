#include "display.h"

WINDOW* newGlassWin() {
  int w = getmaxx(stdscr);
  int y = 2;
  int x = (w - GLASS_WIDTH) / 2;

  WINDOW* res = newwin(GLASS_HEIGHT, GLASS_WIDTH, y, x);
  return res;
}

WINDOW* newInfoWin() {
  int w = getmaxx(stdscr);
  int y = 2;
  int width = 7 + 9;

  WINDOW* res = newwin(1, width, y, w - width - 5);
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

void printInfo(WINDOW* info_win, int score) {
  wmove(info_win, 0, 0);
  wprintw(info_win, "Score: %.9d", score);
  wrefresh(info_win);
}

void initInput() {
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}
