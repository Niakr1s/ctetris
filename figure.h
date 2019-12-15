#ifndef FIGURE_H
#define FIGURE_H

#include "constants.h"
#include "pos.h"

enum {
  FIGURE_MAX_CELLS = 4,
};

enum {
  FIGURE_LINE,
  FIGURE_TRIANGLE,
  FIGURE_BLOCK,
  FIGURE_ZIGZAG,
  FIGURE_MAX,
};

typedef struct Figure {
  Pos pos;
  Pos base_cells[FIGURE_MAX_CELLS];
  Pos cells[FIGURE_MAX_CELLS];
  int name;
  int current_angle;
  int max_angle;
} Figure;

Figure* makeFigure(int name);

void rotateRight(Figure* fig);
void rotateLeft(Figure* fig);
void rotateN(Figure* fig, int angle);

void figureMoveX(Figure* fig, int diff);
void figureMoveY(Figure* fig, int diff);

int figureLeft(Figure* fig);
int figureRight(Figure* fig);
int figureTop(Figure* fig);
int figureBottom(Figure* fig);

#endif  // FIGURE_H
