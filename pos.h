#ifndef POS_H
#define POS_H

#include <vector>

class Pos {
 public:
  Pos(int y, int x);

  Pos reversed() const;
  void moveY(int diff);
  void moveX(int diff);

  Pos operator+(const Pos& rhs) const;
  bool operator==(const Pos& rhs) const;

  int y() const;
  int x() const;
  void setY(int y);
  void setX(int x);

 private:
  int y_, x_;
};

using Poses = std::vector<Pos>;

#endif  // POS_H
