#include "pos.h"

Pos::Pos(int y, int x) : y_(y), x_(x) {}

Pos Pos::reversed() const {
  return Pos(x(), y());
}

void Pos::moveY(int diff) {
  y_ += diff;
}

void Pos::moveX(int diff) {
  x_ += diff;
}

Pos Pos::operator+(const Pos& rhs) const {
  return Pos(y() + rhs.y(), x() + rhs.x());
}

bool Pos::operator==(const Pos& rhs) const {
  return y() == rhs.y() && x() == rhs.x();
}

int Pos::y() const {
  return y_;
}

int Pos::x() const {
  return x_;
}
