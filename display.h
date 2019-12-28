#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif

#include "glass.h"
#include "idisplay.h"

class Display : public IDisplay {
 public:
  Display(int height, int width);
  ~Display();

  void printGlass(const Glass& glass) override;
  void printFigure(std::shared_ptr<IFigure> figure) override;
  void eraseFigure(std::shared_ptr<IFigure> figure) override;
  void printScore(int score) override;
  void printNextFigure(std::shared_ptr<IFigure> next_figure) override;

 private:
  int height_, width_;
  int RIGHT_WINS_X;
  WINDOW* glass_win_;
  WINDOW* info_win_;
  WINDOW* next_figure_win_;

  static void addTitle(WINDOW* win, const char* title);
  static void addFrame(WINDOW* win);

  static const int WINS_START_X;
  static const int WINS_START_Y;
  static const int BORDER_THICKNESS;
  static const int WIN_INFO_WIDTH;
  static const int WIN_INFO_HEIGHT;
  static const int WIN_INFO_Y;
  static const int WIN_NEXT_FIGURE_WIDTH;
  static const int WIN_NEXT_FIGURE_HEIGHT;
  static const int WIN_NEXT_FIGURE_Y;
};

#endif  // DISPLAY_H
