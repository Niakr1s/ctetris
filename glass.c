#include "glass.h"

#include <stdlib.h>

#include "rnd.h"

Glass makeGlass(void) {
  randomInit();
  Glass res;
  for (int row = 0; row != GLASS_HEIGHT; ++row) {
    for (int col = 0; col != GLASS_WIDTH; ++col) {
      res.cells[row][col] = 0;
    }
  }
  res.figure = 0;
  return res;
}

BOOL glassSpawnFigure(Glass* glass, int fig) {
  glass->figure = makeFigure(fig);
  Pos spawn_pos;
  spawn_pos.x = GLASS_WIDTH / 2;
  spawn_pos.y = -figureTop(glass->figure);
  glass->figure->pos = spawn_pos;
  return glassFigureIntersects(glass) ? FALSE : TRUE;
}

int glassSpawnRandomFigure(Glass* glass) {
  int fig = randomZeroToMax(FIGURE_MAX);
  return glassSpawnFigure(glass, fig);
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
  for (int row = GLASS_HEIGHT - 1; row != 0; --row) {
    if (glassRowIsFull(glass, row)) {
      glassShiftDown(glass, row);
      ++row;
    }
  }
}

void glassShiftDown(Glass* glass, int row) {
  for (int to = row; to != -1; --to) {
    int from = to - 1;
    for (int i = 0; i != GLASS_WIDTH; ++i) {
      glass->cells[to][i] = to == 0 ? 0 : glass->cells[from][i];
    }
  }
}

BOOL glassRowIsFull(Glass* glass, int row) {
  for (int col = 0; col != GLASS_WIDTH; ++col) {
    if (!glass->cells[row][col]) {
      return FALSE;
    }
  }
  return TRUE;
}

int glassIsClean(Glass* glass) {
  for (int row = 0; row != GLASS_HEIGHT; ++row) {
    for (int col = 0; col != GLASS_WIDTH; ++col) {
      if (glass->cells[row][col]) {
        return FALSE;
      }
    }
  }
  return TRUE;
}
