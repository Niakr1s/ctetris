#ifndef GLASS_H
#define GLASS_H

#include "constants.h"
#include "figure.h"
#include "pos.h"

enum {
  GLASS_HEIGHT = 20,
  GLASS_WIDTH = 60,
};

typedef struct Glass {
  char cells[GLASS_HEIGHT][GLASS_WIDTH];
  Pos spawn_pos;
  Figure* figure;
} Glass;

Glass makeGlass(void);

void glassSpawnFigure(Glass* glass, char fig);
void glassDeleteFigure(Glass* glass);

void glassFigureMoveX(Glass* glass, int diff);
void glassFigureMoveY(Glass* glass, int diff);

void glassGlueFigure(Glass* glass);
BOOL glassFigureIntersects(Glass* glass);

void glassClearRows(Glass* glass);
void glassShiftDown(Glass* glass);

#endif  // GLASS_H
