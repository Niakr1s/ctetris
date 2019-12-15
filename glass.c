#include "glass.h"

#include "stdlib.h"

Glass makeGlass(void) {
  Glass res;
  for (int row = 0; row != GLASS_HEIGHT; ++row) {
    for (int col = 0; col != GLASS_WIDTH; ++col) {
      res.cells[row][col] = 0;
    }
  }
  res.spawn_pos = makePos(3, GLASS_WIDTH / 2);
  res.figure = 0;
  return res;
}

void glassSpawnFigure(Glass* glass, char fig) {
  glass->figure = makeFigure(glass->spawn_pos, fig);
}

void glassDeleteFigure(Glass* glass) {
  free(glass->figure);
  glass->figure = 0;
}

void glassFigureMoveX(Glass* glass, int diff) {
  if (!glass->figure) {
    return;
  }
  int left = figureLeft(glass->figure);
  int right = figureRight(glass->figure);
  if (diff == 0 || (diff > 0 && GLASS_WIDTH - right <= 1) ||
      (diff < 0 && left <= 0)) {
    return;
  }
  int step = diff > 0 ? 1 : -1;
  figureMoveX(glass->figure, step);
  if (glassFigureIntersects(glass)) {
    figureMoveX(glass->figure, -step);
    glassGlueFigure(glass);
    glassDeleteFigure(glass);
  } else {
    glassFigureMoveX(glass, diff - step);
  }
}

void glassFigureMoveY(Glass* glass, int diff) {
  if (!glass->figure) {
    return;
  }
  int top = figureTop(glass->figure);
  int bot = figureBottom(glass->figure);
  if (diff == 0 || (diff > 0 && GLASS_HEIGHT - bot <= 0) ||
      (diff < 0 && top <= 0)) {
    return;
  }
  int step = diff > 0 ? 1 : -1;
  figureMoveY(glass->figure, step);
  if (glassFigureIntersects(glass)) {
    figureMoveY(glass->figure, -step);
    glassGlueFigure(glass);
    glassDeleteFigure(glass);
  } else {
    glassFigureMoveY(glass, diff - step);
  }
}

void glassGlueFigure(Glass* glass) {
  if (!glass->figure) {
    return;
  }
  for (int i = 0; i != FIGURE_MAX_CELLS; ++i) {
    Pos abs_pos = posToAbsolutePos(glass->figure->cells[i], glass->figure->pos);
    glass->cells[abs_pos.y][abs_pos.x] = 1;
  }
}

BOOL glassFigureIntersects(Glass* glass) {
  if (!glass->figure) {
    return FALSE;
  }
  if (figureBottom(glass->figure) >= GLASS_HEIGHT) {
    return TRUE;
  }
  for (int i = 0; i != FIGURE_MAX_CELLS; ++i) {
    Pos abs_pos = posToAbsolutePos(glass->figure->cells[i], glass->figure->pos);
    if (glass->cells[abs_pos.y][abs_pos.x]) {
      return TRUE;
    }
  }
  return FALSE;
}

void glassClearRows(Glass* glass) {
  for (int i = 0; i != GLASS_WIDTH; ++i) {
    if (!glass->cells[GLASS_HEIGHT - 1][i]) {
      return;
    }
  }
  glassShiftDown(glass);
  glassClearRows(glass);
}

void glassShiftDown(Glass* glass) {
  for (int to = GLASS_HEIGHT - 1; to != -1; --to) {
    int from = to - 1;
    for (int i = 0; i != GLASS_WIDTH; ++i) {
      glass->cells[to][i] = to == 0 ? 0 : glass->cells[from][i];
    }
  }
}
