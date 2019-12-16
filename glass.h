#ifndef GLASS_H
#define GLASS_H

#include "constants.h"
#include "figure.h"
#include "pos.h"

enum {
  GLASS_HEIGHT = 20,
  GLASS_WIDTH = 14,
};

typedef struct Glass {
  char cells[GLASS_HEIGHT][GLASS_WIDTH];
  Figure* figure;
  Figure* next_figure;
} Glass;

Glass makeGlass(void);
void freeGlass(Glass* glass);

Figure* glassMakeFigure(int fig);

BOOL glassSpawnFigure(Glass* glass);
void glassRandomizeNextFigure(Glass* glass);

void glassDeleteFigure(Glass* glass);

void glassFigureMoveX(Glass* glass, int diff);
void glassFigureMoveY(Glass* glass, int diff);

void glassFigureRotateN(Glass* glass, int angle);

void glassGlueFigure(Glass* glass);
BOOL glassFigureIntersects(Glass* glass);

int glassClearRows(Glass* glass);
void glassShiftDown(Glass* glass, int row);

BOOL glassRowIsFull(Glass* glass, int row);
BOOL glassIsClean(Glass* glass);

#endif  // GLASS_H
