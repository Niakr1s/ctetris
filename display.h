#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>

#include "glass.h"

enum {
  WINS_START_X = 2,
  WINS_START_Y = 1,
  BORDER_THICKNESS = 1,
  RIGHT_WINS_X = WINS_START_X + GLASS_WIDTH + BORDER_THICKNESS * 2 + 2,
  WIN_INFO_WIDTH = 7 + 9,
  WIN_INFO_HEIGHT = 1,
  WIN_INFO_Y = WINS_START_Y,
  WIN_NEXT_FIGURE_WIDTH = WIN_INFO_WIDTH,
  WIN_NEXT_FIGURE_HEIGHT = 10,
  WIN_NEXT_FIGURE_Y = WIN_INFO_Y + WIN_INFO_HEIGHT + BORDER_THICKNESS * 2,
};

WINDOW* newGlassWin(void);
WINDOW* newInfoWin(void);
WINDOW* newNextFigureWin(void);

void printGlass(WINDOW* win, Glass* glass);
void printFrame(WINDOW* win);
void printInfo(WINDOW* info_win, int score);

void initInput(void);

#endif  // DISPLAY_H
