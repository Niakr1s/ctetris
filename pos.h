#ifndef POS_H
#define POS_H

typedef struct Pos {
  int y, x;
} Pos;

Pos makePos(int y, int x);

Pos reversedPos(Pos pos);

void posMoveX(Pos* pos, int diff);
void posMoveY(Pos* pos, int diff);

Pos posToAbsolutePos(Pos pos, Pos currentPos);

#endif  // POS_H
