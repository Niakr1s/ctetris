#ifndef GLASS_H
#define GLASS_H

#include <memory>
#include <vector>

#include "ifigure.h"
#include "ifigurefactory.h"
#include "pos.h"

class Glass {
 public:
  using Cells = std::vector<std::vector<char>>;

  Glass(int height, int width);

  int height() const;
  int width() const;

  void spawnFigure();
  void spawnNextFigure();
  bool figureIntersects() const;

  void figureMoveX(int diff);
  bool figureMoveY(int diff);  // true if figure glued
  void figureRotateN(int times);

  void glueFigure();
  int clearRows();
  bool isClean() const;

  const Cells &cells() const;
  std::shared_ptr<IFigure> figure() const;
  std::shared_ptr<IFigure> next_figure() const;

  static const char EMPTY_CELL;

 private:
  int height_, width_, figure_center_x;
  Cells cells_;
  char color_;  // when glued, figure becomes colored with numbers 1..=9
  std::shared_ptr<IFigure> figure_;
  std::shared_ptr<IFigure> next_figure_;
  std::shared_ptr<IFigureFactory> figure_factory_;

  bool rowIsFull(int row) const;
  void shiftDown(int row);
  void figureMoveInside();

  void incrColor();
};

#endif  // GLASS_H
