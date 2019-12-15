#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>

#include "glass.h"

WINDOW* newGlassWin(void);
WINDOW* newInfoWin(void);

void printGlass(WINDOW* win, Glass* glass);
void printFrame(WINDOW* win);
void printInfo(WINDOW* info_win, int score);

void initInput(void);

#endif  // DISPLAY_H
