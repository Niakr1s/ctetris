#include "pos.h"

Pos makePos(int y, int x) {
  Pos pos;
  pos.y = y;
  pos.x = x;
  return pos;
}

Pos reversedPos(Pos pos) {
  Pos res;
  res.x = pos.y;
  res.y = pos.x;
  return res;
}

void posMoveX(Pos* pos, int diff) {
  pos->x += diff;
}

void posMoveY(Pos* pos, int diff) {
  pos->y += diff;
}

Pos posToAbsolutePos(Pos pos, Pos currentPos) {
  pos.x += currentPos.x;
  pos.y += currentPos.y;
  return pos;
}
