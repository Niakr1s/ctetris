#include "consoledisplay.h"

#include <stdlib.h>

ConsoleDisplay::ConsoleDisplay(int height, int width)
    : height_(height),
      width_(width),
      RIGHT_WINS_X(WINS_START_X + width + BORDER_THICKNESS * 2 + 2) {
  initscr();
  curs_set(0);
  noecho();

  glass_win_ = newwin(height, width, WINS_START_Y, WINS_START_X);
  info_win_ =
      newwin(WIN_INFO_HEIGHT, WIN_INFO_WIDTH, WINS_START_Y, RIGHT_WINS_X);
  next_figure_win_ = newwin(WIN_NEXT_FIGURE_HEIGHT, WIN_NEXT_FIGURE_WIDTH,
                            WIN_NEXT_FIGURE_Y, RIGHT_WINS_X);

  addTitle(next_figure_win_, "Next figure: ");
  addFrame(glass_win_);
  refresh();
}

ConsoleDisplay::~ConsoleDisplay() { endwin(); }

void ConsoleDisplay::printGlass(const Glass& glass) {
  wclear(glass_win_);
  for (int row = 0; row != height_; ++row) {
    for (int col = 0; col != width_; ++col) {
      mvwaddch(glass_win_, row, col, glass.cells()[row][col]);
    }
  }
}

void ConsoleDisplay::printFigure(std::shared_ptr<IFigure> figure) {
  auto cells = figure->absolutePoses();
  for (auto& cell : cells) {
    mvwaddch(glass_win_, cell.y(), cell.x(), 'O');
  }
  wrefresh(glass_win_);
}

void ConsoleDisplay::eraseFigure(std::shared_ptr<IFigure> figure) {
  auto cells = figure->absolutePoses();
  for (auto& cell : cells) {
    mvwaddch(glass_win_, cell.y(), cell.x(), ' ');
  }
  wrefresh(glass_win_);
}

void ConsoleDisplay::printScore(int score) {
  wmove(info_win_, 0, 0);
  wprintw(info_win_, "Score: %.9d", score);
  wrefresh(info_win_);
}

void ConsoleDisplay::printNextFigure(std::shared_ptr<IFigure> next_figure) {
  wclear(next_figure_win_);
  Pos tmp_base = {WIN_NEXT_FIGURE_HEIGHT / 2 - 1, 5};
  auto cells = next_figure->absolutePoses();
  for (auto& cell : cells) {
    mvwaddch(next_figure_win_, cell.y() + tmp_base.y(), cell.x() + tmp_base.x(),
             '0');
  }
  wrefresh(next_figure_win_);
}

int ConsoleDisplay::height() const { return height_; }

int ConsoleDisplay::width() const { return width_; }

void ConsoleDisplay::addTitle(WINDOW* win, const char* title) {
  int y, x;
  getbegyx(win, y, x);
  mvaddstr(y - 1, x, title);
  refresh();
}

void ConsoleDisplay::addFrame(WINDOW* win) {
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

const int ConsoleDisplay::WINS_START_X = 2;
const int ConsoleDisplay::WINS_START_Y = 1;
const int ConsoleDisplay::BORDER_THICKNESS = 1;
const int ConsoleDisplay::WIN_INFO_WIDTH = 7 + 9;
const int ConsoleDisplay::WIN_INFO_HEIGHT = 1;
const int ConsoleDisplay::WIN_INFO_Y = WINS_START_Y;
const int ConsoleDisplay::WIN_NEXT_FIGURE_WIDTH = WIN_INFO_WIDTH;
const int ConsoleDisplay::WIN_NEXT_FIGURE_HEIGHT = 6;
const int ConsoleDisplay::WIN_NEXT_FIGURE_Y =
    WIN_INFO_Y + WIN_INFO_HEIGHT + BORDER_THICKNESS * 3;
