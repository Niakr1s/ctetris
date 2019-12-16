#include "figure.h"

#include "math.h"
#include "stdlib.h"

void rotateRight(Figure* fig) {
  rotateN(fig, 1);
}

void rotateLeft(Figure* fig) {
  rotateN(fig, -1);
}

void rotateN(Figure* fig, int angle) {
  angle %= fig->max_angle;
  while (angle < 0) {
    angle += fig->max_angle;
  }
  if (angle == 0) {
    return;
  }
  fig->current_angle = ++fig->current_angle % fig->max_angle;
  for (int i = 0; i != FIGURE_MAX_CELLS; ++i) {
    if (fig->current_angle == 0) {
      fig->cells[i] = fig->base_cells[i];
    } else {
      fig->cells[i] = reversedPos(fig->cells[i]);
      fig->cells[i].x = -fig->cells[i].x;
    }
  }
  rotateN(fig, angle - 1);
}

Figure* makeFigure(int name) {
  Figure* fig = malloc(sizeof(Figure));
  fig->pos.x = 0;
  fig->pos.y = 0;
  fig->current_angle = 0;
  switch (name) {
    case (FIGURE_LINE):
      fig->name = FIGURE_LINE;
      fig->base_cells[0] = makePos(-1, 0);
      fig->base_cells[1] = makePos(0, 0);
      fig->base_cells[2] = makePos(1, 0);
      fig->base_cells[3] = makePos(2, 0);
      fig->max_angle = 2;
      break;
    case (FIGURE_TRIANGLE):
      fig->name = FIGURE_TRIANGLE;
      fig->base_cells[0] = makePos(-1, 0);
      fig->base_cells[1] = makePos(0, -1);
      fig->base_cells[2] = makePos(0, 0);
      fig->base_cells[3] = makePos(0, 1);
      fig->max_angle = 4;
      break;
    case (FIGURE_BLOCK):
      fig->name = FIGURE_BLOCK;
      fig->base_cells[0] = makePos(0, 0);
      fig->base_cells[1] = makePos(0, 1);
      fig->base_cells[2] = makePos(1, 0);
      fig->base_cells[3] = makePos(1, 1);
      fig->max_angle = 1;
      break;
    case (FIGURE_ZIGZAG_RIGHT):
      fig->name = FIGURE_ZIGZAG_RIGHT;
      fig->base_cells[0] = makePos(-1, 1);
      fig->base_cells[1] = makePos(0, 1);
      fig->base_cells[2] = makePos(0, 0);
      fig->base_cells[3] = makePos(1, 0);
      fig->max_angle = 2;
      break;
    case (FIGURE_ZIGZAG_LEFT):
      fig->name = FIGURE_ZIGZAG_LEFT;
      fig->base_cells[0] = makePos(-1, -1);
      fig->base_cells[1] = makePos(0, -1);
      fig->base_cells[2] = makePos(0, 0);
      fig->base_cells[3] = makePos(1, 0);
      fig->max_angle = 2;
      break;
    case (FIGURE_G_RIGHT):
      fig->name = FIGURE_G_RIGHT;
      fig->base_cells[0] = makePos(-1, 1);
      fig->base_cells[1] = makePos(-1, 0);
      fig->base_cells[2] = makePos(0, 0);
      fig->base_cells[3] = makePos(1, 0);
      fig->max_angle = 4;
      break;
    case (FIGURE_G_LEFT):
      fig->name = FIGURE_G_LEFT;
      fig->base_cells[0] = makePos(-1, -1);
      fig->base_cells[1] = makePos(-1, 0);
      fig->base_cells[2] = makePos(0, 0);
      fig->base_cells[3] = makePos(1, 0);
      fig->max_angle = 4;
      break;
    default:
      fig->name = FIGURE_MAX;
  }
  for (int i = 0; i != FIGURE_MAX_CELLS; ++i) {
    fig->cells[i] = fig->base_cells[i];
  }
  return fig;
}

void figureMoveX(Figure* fig, int diff) {
  posMoveX(&fig->pos, diff);
}

void figureMoveY(Figure* fig, int diff) {
  posMoveY(&fig->pos, diff);
}

int figureLeft(Figure* fig) {
  int res = fig->cells[0].x;
  for (int i = 1; i != FIGURE_MAX_CELLS; ++i) {
    if (fig->cells[i].x < res) {
      res = fig->cells[i].x;
    }
  }
  res += fig->pos.x;
  return res;
}

int figureRight(Figure* fig) {
  int res = fig->cells[0].x;
  for (int i = 1; i != FIGURE_MAX_CELLS; ++i) {
    if (fig->cells[i].x > res) {
      res = fig->cells[i].x;
    }
  }
  res += fig->pos.x;
  return res;
}

int figureTop(Figure* fig) {
  int res = fig->cells[0].y;
  for (int i = 1; i != FIGURE_MAX_CELLS; ++i) {
    if (fig->cells[i].y < res) {
      res = fig->cells[i].y;
    }
  }
  res += fig->pos.y;
  return res;
}

int figureBottom(Figure* fig) {
  int res = fig->cells[0].y;
  for (int i = 1; i != FIGURE_MAX_CELLS; ++i) {
    if (fig->cells[i].y > res) {
      res = fig->cells[i].y;
    }
  }
  res += fig->pos.y;
  return res;
}
