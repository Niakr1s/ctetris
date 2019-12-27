#ifndef IFIGURE_H
#define IFIGURE_H

#include "pos.h"

class IFigure {
 public:
  enum class Type : int {
    FIGURE_LINE,
    FIGURE_TRIANGLE,
    FIGURE_BLOCK,
    FIGURE_ZIGZAG_RIGHT,
    FIGURE_ZIGZAG_LEFT,
    FIGURE_G_RIGHT,
    FIGURE_G_LEFT,
    FIGURE_MAX,
  };

  virtual ~IFigure() = default;

  virtual void setPos(int y, int x) = 0;
  virtual Poses absolutePoses() const = 0;

  virtual void rotateN(int times) = 0;
  virtual void moveX(int diff) = 0;
  virtual void moveY(int diff) = 0;

  virtual int left() const = 0;
  virtual int right() const = 0;
  virtual int top() const = 0;
  virtual int bottom() const = 0;

  virtual int currentAngle() const = 0;
  virtual int maxAngle() const = 0;
};

#endif  // IFIGURE_H
