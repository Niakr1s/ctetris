#ifndef ABSTRACTFIGURE_H
#define ABSTRACTFIGURE_H

class AbstractFigure {
 public:
  virtual ~AbstractFigure() = default;

  virtual void rotateN(int times) = 0;
  virtual void moveX(int diff) = 0;
  virtual void moveY(int diff) = 0;

  virtual int left() const = 0;
  virtual int right() const = 0;
  virtual int top() const = 0;
  virtual int bottom() const = 0;
};

#endif  // ABSTRACTFIGURE_H
