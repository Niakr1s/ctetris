#ifndef GLASS_H
#define GLASS_H

#include <memory>
#include <vector>

#include "figurefactory.h"
#include "ifigure.h"
#include "pos.h"

class GlassIsFullException : std::exception {};

class Glass {
 public:
  Glass(int height = 20, int width = 14);

  int height() const;
  int width() const;

  void spawnFigure();
  bool figureIntersects() const;

  void figureMoveX(int diff);
  void figureMoveY(int diff);
  void figureRotateN(int times);

  void glueFigure();
  int clearRows();
  bool isClean() const;

 private:
  int height_, width_;
  std::vector<std::vector<bool>> cells_;
  std::shared_ptr<IFigure> figure_;
  std::shared_ptr<IFigure> next_figure_;
  std::shared_ptr<IFigureFactory> figure_factory_;

  bool rowIsFull(int row) const;
  void shiftDown(int row);

  static const char EMPTY_CELL;
  static const char FILLED_CELL;
};

#endif  // GLASS_H
