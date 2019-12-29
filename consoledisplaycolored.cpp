#include "consoledisplaycolored.h"

ConsoleDisplayColored::ConsoleDisplayColored(int height, int width)
    : ConsoleDisplay(height, width) {
  start_color();
  init_pair(COLOR1, COLOR_RED, COLOR_RED);
  init_pair(COLOR2, COLOR_GREEN, COLOR_GREEN);
  init_pair(COLOR3, COLOR_BLUE, COLOR_BLUE);
  init_pair(COLOR_FIGURE, COLOR_CYAN, COLOR_CYAN);
  init_pair(COLOR_SCORE, COLOR_RED, COLOR_BLACK);
}

void ConsoleDisplayColored::printGlass(const Glass &glass) {
  wclear(glass_win_);
  for (int row = 0; row != height_; ++row) {
    for (int col = 0; col != width_; ++col) {
      char ch = glass.cells()[row][col];
      int color = charToColor(ch);
      wattron(glass_win_, COLOR_PAIR(color));
      mvwaddch(glass_win_, row, col, ' ');
      wattroff(glass_win_, COLOR_PAIR(color));
    }
  }
  wrefresh(glass_win_);
}

void ConsoleDisplayColored::printFigure(std::shared_ptr<IFigure> figure) {
  wattron(glass_win_, COLOR_PAIR(COLOR_FIGURE));
  ConsoleDisplay::printFigure(figure);
  wattroff(glass_win_, COLOR_PAIR(COLOR_FIGURE));
}

void ConsoleDisplayColored::printNextFigure(
    std::shared_ptr<IFigure> next_figure) {
  wattron(next_figure_win_, COLOR_PAIR(COLOR_FIGURE));
  ConsoleDisplay::printNextFigure(next_figure);
  wattroff(next_figure_win_, COLOR_PAIR(COLOR_FIGURE));
}

int ConsoleDisplayColored::charToColor(char ch) {
  return ((ch - '1') % (COLOR_MAX - 1) + 1);
}
