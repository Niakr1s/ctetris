#ifndef IDISPLAY_H
#define IDISPLAY_H

#include "glass.h"

class IDisplay {
 public:
  virtual void printGlass(const Glass& glass) = 0;
  virtual void printFigure(std::shared_ptr<IFigure> figure) = 0;
  virtual void eraseFigure(std::shared_ptr<IFigure> figure) = 0;
  virtual void printScore(int score) = 0;
  virtual void printNextFigure(std::shared_ptr<IFigure> next_figure) = 0;

  virtual void showPauseMenu() = 0;
  virtual void hidePauseMenu() = 0;

  virtual int height() const = 0;
  virtual int width() const = 0;
};

#endif  // IDISPLAY_H
