#ifndef POS_H
#define POS_H

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

 private:
  int y_, x_;
};

#endif  // POS_H
