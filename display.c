#include "display.h"

#include <stdlib.h>

WINDOW* newGlassWin() {
  WINDOW* res = newwin(GLASS_HEIGHT, GLASS_WIDTH, WINS_START_Y, WINS_START_X);
  return res;
}

WINDOW* newInfoWin() {
  WINDOW* res =
      newwin(WIN_INFO_HEIGHT, WIN_INFO_WIDTH, WINS_START_Y, RIGHT_WINS_X);
  return res;
}

WINDOW* newNextFigureWin() {
  WINDOW* res = newwin(WIN_NEXT_FIGURE_HEIGHT, WIN_NEXT_FIGURE_WIDTH,
                       WIN_NEXT_FIGURE_Y, RIGHT_WINS_X);
  addTitle(res, "Next figure:");
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
  mvwaddch(stdscr, y - 1, x - 1, '+');
  mvwaddch(stdscr, y - 1, x + w, '+');
  mvwaddch(stdscr, y + h, x - 1, '+');
  mvwaddch(stdscr, y + h, x + w, '+');
  refresh();
}

void printInfo(WINDOW* info_win, int score) {
  wmove(info_win, 0, 0);
  wprintw(info_win, "Score: %.9d", score);
  wrefresh(info_win);
}

void printNextFigure(WINDOW* next_figure_win, Figure* fig) {
  wclear(next_figure_win);
  wmove(next_figure_win, 0, 0);
  Pos tmp_base = {WIN_NEXT_FIGURE_HEIGHT / 2 - 1, 5};
  for (int i = 0; i != FIGURE_MAX_CELLS; ++i) {
    Pos tmp = posToAbsolutePos(fig->cells[i], tmp_base);
    mvwaddch(next_figure_win, tmp.y, tmp.x, '0');
  }
  wrefresh(next_figure_win);
}

void addTitle(WINDOW* win, const char* str) {
  int y, x;
  getbegyx(win, y, x);
  mvaddstr(y - 1, x, str);
  refresh();
}

void initInput() {
  curs_set(0);
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}
