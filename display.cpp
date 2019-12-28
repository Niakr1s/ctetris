#include "display.h"

#include <stdlib.h>

Display::Display(int height, int width)
    : height_(height),
      width_(width),
      RIGHT_WINS_X(WINS_START_X + width + BORDER_THICKNESS * 2 + 2) {
  initscr();
  initInput();

  glass_win_ = newwin(height, width, WINS_START_Y, WINS_START_X);
  info_win_ =
      newwin(WIN_INFO_HEIGHT, WIN_INFO_WIDTH, WINS_START_Y, RIGHT_WINS_X);
  next_figure_win_ = newwin(WIN_NEXT_FIGURE_HEIGHT, WIN_NEXT_FIGURE_WIDTH,
                            WIN_NEXT_FIGURE_Y, RIGHT_WINS_X);

  addTitle(next_figure_win_, "Next figure: ");
  addFrame(glass_win_);
  refresh();
}

Display::~Display() { endwin(); }

void Display::printGlass(const Glass& glass) {
  wclear(glass_win_);
  for (int row = 0; row != height_; ++row) {
    for (int col = 0; col != width_; ++col) {
      mvwaddch(glass_win_, row, col, glass.cells()[row][col]);
    }
  }
  printFigure(glass.figure());
}

void Display::printFigure(std::shared_ptr<IFigure> figure) {
  auto cells = figure->absolutePoses();
  for (auto& cell : cells) {
    mvwaddch(glass_win_, cell.y(), cell.x(), 'O');
  }
  wrefresh(glass_win_);
}

void Display::eraseFigure(std::shared_ptr<IFigure> figure) {
  auto cells = figure->absolutePoses();
  for (auto& cell : cells) {
    mvwaddch(glass_win_, cell.y(), cell.x(), ' ');
  }
  wrefresh(glass_win_);
}

void Display::printScore(int score) {
  wmove(info_win_, 0, 0);
  wprintw(info_win_, "Score: %.9d", score);
  wrefresh(info_win_);
}

void Display::printNextFigure(std::shared_ptr<IFigure> next_figure) {
  wclear(next_figure_win_);
  Pos tmp_base = {WIN_NEXT_FIGURE_HEIGHT / 2 - 1, 5};
  auto cells = next_figure->absolutePoses();
  for (auto& cell : cells) {
    mvwaddch(next_figure_win_, cell.y() + tmp_base.y(), cell.x() + tmp_base.x(),
             '0');
  }
  wrefresh(next_figure_win_);
}

void Display::initInput() {
  curs_set(0);
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}

void Display::addTitle(WINDOW* win, const char* title) {
  int y, x;
  getbegyx(win, y, x);
  mvaddstr(y - 1, x, title);
  refresh();
}

void Display::addFrame(WINDOW* win) {
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

const int Display::WINS_START_X = 2;
const int Display::WINS_START_Y = 1;
const int Display::BORDER_THICKNESS = 1;
const int Display::WIN_INFO_WIDTH = 7 + 9;
const int Display::WIN_INFO_HEIGHT = 1;
const int Display::WIN_INFO_Y = WINS_START_Y;
const int Display::WIN_NEXT_FIGURE_WIDTH = WIN_INFO_WIDTH;
const int Display::WIN_NEXT_FIGURE_HEIGHT = 6;
const int Display::WIN_NEXT_FIGURE_Y =
    WIN_INFO_Y + WIN_INFO_HEIGHT + BORDER_THICKNESS * 3;
