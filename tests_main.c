#include <assert.h>
#include <stdio.h>

#include "figure.h"
#include "glass.h"
#include "pos.h"

void glassFigureMoveXTests() {
  Glass glass = makeGlass();
  glass.figure = makeFigure(FIGURE_ZIGZAG);

  int diff = 1;
  Pos from = glass.figure->pos;
  glassFigureMoveX(&glass, diff);
  Pos to = glass.figure->pos;
  assert((from.x + diff) == to.x && from.y == to.y);
  from = to;

  diff = -2;
  glassFigureMoveX(&glass, diff);
  to = glass.figure->pos;
  assert((from.x + diff) == to.x && from.y == to.y);
  from = to;

  printf("glassFigureMoveXTests done\n");
}

void figureLeftTests() {
  Figure* figure = makeFigure(FIGURE_ZIGZAG);
  assert(figureLeft(figure) == 0);

  printf("figureLeftTests done\n");
}

int main(int argc, char* argv[]) {
  glassFigureMoveXTests();
  figureLeftTests();
  return 0;
}
