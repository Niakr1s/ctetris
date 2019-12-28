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
};

#endif  // IDISPLAY_H
