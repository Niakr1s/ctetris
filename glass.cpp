#include "glass.h"

#include <stdlib.h>

#include "randomfigurefactory.h"
#include "rnd.h"
#include "standardfigure.h"

Glass::Glass(int height, int width)
    : height_(height),
      width_(width),
      figure_factory_(std::make_shared<RandomFigureFactory<StandardFigure>>()) {
  cells_.resize(height_);
  for (int row = 0; row != height_; ++row) {
    cells_[0].reserve(width_);
    for (int col = 0; col != width_; ++col) {
      cells_[row].push_back(EMPTY_CELL);
    }
  }
  figure_ = figure_factory_->nextFigure();
  next_figure_ = figure_factory_->nextFigure();
}

int Glass::height() const { return height_; }
int Glass::width() const { return width_; }

void Glass::spawnFigure() {
  figure_ = next_figure_;
  next_figure_ = figure_factory_->nextFigure();
  if (figureIntersects()) {
    throw GlassIsFullException();
  }
}

bool Glass::figureIntersects() const {
  if (figure_->bottom() >= height()) {
    return true;
  }
  auto abs_poses = figure_->absolutePoses();
  for (auto& p : abs_poses) {
    if (cells_[p.y()][p.x()] != EMPTY_CELL) {
      return true;
    }
  }
  return false;
}

void Glass::figureMoveX(int diff) {
  if (diff == 0 || (diff > 0 && width() - figure_->right() <= 1) ||
      (diff < 0 && figure_->left() <= 0)) {
    return;
  }
  int step = diff > 0 ? 1 : -1;
  figure_->moveX(step);
  if (figureIntersects()) {
    figure_->moveX(-step);
  } else {
    figureMoveX(diff - step);
  }
}

void Glass::figureMoveY(int diff) {
  if (diff == 0 || (diff > 0 && height() - figure_->bottom() <= 0) ||
      (diff < 0 && figure_->top() <= 0)) {
    return;
  }
  int step = diff > 0 ? 1 : -1;
  figure_->moveY(step);
  if (figureIntersects()) {
    figure_->moveY(-step);
    glueFigure();
    spawnFigure();
  } else {
    figureMoveY(diff - step);
  }
}

void Glass::figureRotateN(int times) {
  figure_->rotateN(times);
  if (figure_->left() < 0) {
    figureMoveX(-figure_->left());
  }
  if (figure_->right() >= width()) {
    figureMoveX(width() - figure_->right() - 1);
  }
}

void Glass::glueFigure() {
  auto abs_poses = figure_->absolutePoses();
  for (auto& pos : abs_poses) {
    cells_[pos.y()][pos.x()] = FILLED_CELL;
  }
}

int Glass::clearRows() {
  int res = 0;
  for (int row = height() - 1; row != 0; --row) {
    if (rowIsFull(row)) {
      shiftDown(row);
      ++res;
      ++row;
    }
  }
  return res;
}

bool Glass::isClean() const {
  for (int row = 0; row != height(); ++row) {
    for (int col = 0; col != width(); ++col) {
      if (cells_[row][col] != EMPTY_CELL) {
        return false;
      }
    }
  }
  return true;
}

bool Glass::rowIsFull(int row) const {
  for (int col = 0; col != width(); ++col) {
    if (cells_[row][col] != FILLED_CELL) {
      return false;
    }
  }
  return true;
}

void Glass::shiftDown(int row) {
  for (int to = row; to != -1; --to) {
    int from = to - 1;
    for (int i = 0; i != width(); ++i) {
      cells_[to][i] =
          (to == 0) ? EMPTY_CELL
                    : cells_[from][i];  // (to == 0) ? ... - for topmost row
    }
  }
}

const char Glass::EMPTY_CELL = ' ';
const char Glass::FILLED_CELL = 'X';
