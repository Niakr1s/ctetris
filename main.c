#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#include "display.h"
#include "figure.h"
#include "math.h"
#include "pos.h"

int main() {
  initscr();
  WINDOW* glass_win = newGlassWin();
  Glass glass = makeGlass();
  glass.figure = makeFigure(glass.spawn_pos, FIGURE_ZIGZAG);
  gameLoop(glass_win, &glass);
  endwin();
  return 0;
}
