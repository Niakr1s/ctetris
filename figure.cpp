#include "figure.h"

#include <algorithm>
#include <stdexcept>

#include "math.h"
#include "stdlib.h"

Figure::Figure(Figure::Type type)
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

void Figure::setPos(int y, int x) { pos_ = {y, x}; }

Poses Figure::absolutePoses() const {
  Poses res;
  for (size_t i = 0; i != size(); ++i) {
    res.push_back(cells_[i] + pos_);
  }
  return res;
}

void Figure::rotateN(int times) {
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

void Figure::moveX(int diff) { pos_.moveX(diff); }

void Figure::moveY(int diff) { pos_.moveY(diff); }

int Figure::left() const {
  auto res =
      std::min_element(cells_.cbegin(), cells_.cend(), pos_compare_x)->x();
  res += pos_.x();
  return res;
}

int Figure::right() const {
  auto res =
      std::max_element(cells_.cbegin(), cells_.cend(), pos_compare_x)->x();
  res += pos_.x();
  return res;
}

int Figure::top() const {
  auto res =
      std::min_element(cells_.cbegin(), cells_.cend(), pos_compare_y)->y();
  res += pos_.y();
  return res;
}

int Figure::bottom() const {
  auto res =
      std::max_element(cells_.cbegin(), cells_.cend(), pos_compare_y)->y();
  res += pos_.y();
  return res;
}

int Figure::currentAngle() const { return current_angle_; }

int Figure::maxAngle() const { return max_angle_; }

size_t Figure::size() const { return cells_.size(); }

int Figure::simplify(int times) const {
  times %= max_angle_;
  while (times < 0) {
    times += max_angle_;
  }
  return times;
}

bool pos_compare_x(const Pos& lhs, const Pos& rhs) { return lhs.x() < rhs.x(); }

bool pos_compare_y(const Pos& lhs, const Pos& rhs) { return lhs.y() < rhs.y(); }
