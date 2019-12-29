#ifndef CONSOLEDISPLAYCOLORED_H
#define CONSOLEDISPLAYCOLORED_H

#include "consoledisplay.h"

class ConsoleDisplayColored : public ConsoleDisplay {
 public:
  ConsoleDisplayColored(int height, int width);

  enum {
    COLOR1 = 1,
    COLOR2,
    COLOR3,
    COLOR_MAX,
    COLOR_FIGURE,
    COLOR_SCORE,
  };

  void printGlass(const Glass &glass) override;
  void printFigure(std::shared_ptr<IFigure> figure) override;
  void printNextFigure(std::shared_ptr<IFigure> next_figure) override;

 private:
  static int charToColor(char ch);  // from 1 to 3
};

#endif  // CONSOLEDISPLAYCOLORED_H
