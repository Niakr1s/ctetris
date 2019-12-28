#ifndef FIGURE_H
#define FIGURE_H

#include "ifigure.h"
#include "pos.h"

class Figure : public IFigure {
 public:
  enum class Type : int {
    FIGURE_LINE,
    FIGURE_TRIANGLE,
    FIGURE_BLOCK,
    FIGURE_ZIGZAG_RIGHT,
    FIGURE_ZIGZAG_LEFT,
    FIGURE_G_RIGHT,
    FIGURE_G_LEFT,
    MAX,
  };

  Figure(Type type);

  // IFigure interface
 public:
  void setPos(int y, int x) override;
  Poses absolutePoses() const override;
  void rotateN(int times) override;
  void moveX(int diff) override;
  void moveY(int diff) override;
  int left() const override;
  int right() const override;
  int top() const override;
  int bottom() const override;
  int currentAngle() const override;
  int maxAngle() const override;

 private:
  Pos pos_;
  Poses base_cells_;
  Poses cells_;
  Type type_;
  int current_angle_;
  int max_angle_;

 private:
  size_t size() const;
  int simplify(int times) const;
};

bool pos_compare_x(const Pos& lhs, const Pos& rhs);
bool pos_compare_y(const Pos& lhs, const Pos& rhs);

#endif  // FIGURE_H
