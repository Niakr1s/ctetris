#include "tetrisfigure.h"

#include <algorithm>
#include <stdexcept>

#include "math.h"
#include "stdlib.h"

TetrisFigure::TetrisFigure(TetrisFigure::Type type)
    : pos_(0, 0), type_(type), current_angle_(0) {
  base_cells_.reserve(5);
  cells_.reserve(5);

  switch (type_) {
    case (Type::FIGURE_LINE):
      base_cells_ = {{-1, 0}, {0, 0}, {1, 0}, {2, 0}};
      max_angle_ = 2;
      break;
    case (Type::FIGURE_TRIANGLE):
      base_cells_ = {{-1, 0}, {0, -1}, {0, 0}, {0, 1}};
      max_angle_ = 4;
      break;
    case (Type::FIGURE_BLOCK):
      base_cells_ = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
      max_angle_ = 1;
      break;
    case (Type::FIGURE_ZIGZAG_RIGHT):
      base_cells_ = {{-1, 1}, {0, 1}, {0, 0}, {1, 0}};
      max_angle_ = 2;
      break;
    case (Type::FIGURE_ZIGZAG_LEFT):
      base_cells_ = {{-1, -1}, {0, -1}, {0, 0}, {1, 0}};
      max_angle_ = 2;
      break;
    case (Type::FIGURE_G_RIGHT):
      base_cells_ = {{-1, 1}, {-1, 0}, {0, 0}, {1, 0}};
      max_angle_ = 4;
      break;
    case (Type::FIGURE_G_LEFT):
      base_cells_ = {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}};
      max_angle_ = 4;
      break;
    default:
      throw std::runtime_error("StandardFigure: not valid type in constructor");
  }
  cells_ = base_cells_;
}

void TetrisFigure::setPos(int y, int x) { pos_ = {y, x}; }

Poses TetrisFigure::absolutePoses() const {
  Poses res;
  for (size_t i = 0; i != size(); ++i) {
    res.push_back(cells_[i] + pos_);
  }
  return res;
}

void TetrisFigure::rotateN(int times) {
  times = simplify(times);
  if (times == 0) {
    return;
  }
  current_angle_ = ++current_angle_ % max_angle_;
  if (current_angle_ == 0) {
    cells_ = base_cells_;
  } else {
    for (size_t i = 0; i != size(); ++i) {
      cells_[i] = cells_[i].reversed();
      cells_[i].setX(-cells_[i].x());
    }
  }
  rotateN(times - 1);
}

void TetrisFigure::moveX(int diff) { pos_.moveX(diff); }

void TetrisFigure::moveY(int diff) { pos_.moveY(diff); }

int TetrisFigure::left() const {
  auto res =
      std::min_element(cells_.cbegin(), cells_.cend(), pos_compare_x)->x();
  res += pos_.x();
  return res;
}

int TetrisFigure::right() const {
  auto res =
      std::max_element(cells_.cbegin(), cells_.cend(), pos_compare_x)->x();
  res += pos_.x();
  return res;
}

int TetrisFigure::top() const {
  auto res =
      std::min_element(cells_.cbegin(), cells_.cend(), pos_compare_y)->y();
  res += pos_.y();
  return res;
}

int TetrisFigure::bottom() const {
  auto res =
      std::max_element(cells_.cbegin(), cells_.cend(), pos_compare_y)->y();
  res += pos_.y();
  return res;
}

int TetrisFigure::currentAngle() const { return current_angle_; }

int TetrisFigure::maxAngle() const { return max_angle_; }

size_t TetrisFigure::size() const { return cells_.size(); }

int TetrisFigure::simplify(int times) const {
  times %= max_angle_;
  while (times < 0) {
    times += max_angle_;
  }
  return times;
}

bool pos_compare_x(const Pos& lhs, const Pos& rhs) { return lhs.x() < rhs.x(); }

bool pos_compare_y(const Pos& lhs, const Pos& rhs) { return lhs.y() < rhs.y(); }
