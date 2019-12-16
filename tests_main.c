#include <assert.h>
#include <stdio.h>

#include "constants.h"
#include "figure.h"
#include "glass.h"
#include "pos.h"

void glassFigureMoveXTests() {
  Glass glass = makeGlass();
  glassSpawnFigure(&glass);

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

void glassShiftDownTests() {
  Glass glass = makeGlass();
  for (int row = 0; row != GLASS_HEIGHT; ++row) {
    for (int col = 0; col != GLASS_WIDTH; ++col) {
      glass.cells[row][col] = 1;
    }
  }
  glassClearRows(&glass);
  assert(glassIsClean(&glass) == TRUE);

  printf("glassShiftDownTests done\n");
}

int main(int argc, char* argv[]) {
  glassFigureMoveXTests();
  glassShiftDownTests();
  return 0;
}
