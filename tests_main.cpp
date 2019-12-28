#include <assert.h>
#include <stdio.h>

#include "glass.h"
#include "pos.h"
#include "standardfigure.h"

void glassFigureSpawnsAtTopTest() {
  Glass glass;
  assert(glass.figure()->top() == 0);
}

void standardFigureTopLeftDownBottomTest() {
  StandardFigure fig(StandardFigure::Type::FIGURE_ZIGZAG_RIGHT);
  fig.setPos(3, 3);
  assert(fig.left() == 3);
  assert(fig.right() == 4);
  assert(fig.top() == 2);
  assert(fig.bottom() == 4);
}

int main() {
  glassFigureSpawnsAtTopTest();
  standardFigureTopLeftDownBottomTest();
  return 0;
}
