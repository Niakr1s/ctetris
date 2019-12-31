#include "game.h"

#include <time.h>

#include <chrono>
#include <functional>
#include <thread>

#include "consolekeyboardcontroller.h"
#include "gamestate.h"

using namespace std::chrono_literals;

Game::Game()
    : Game(std::make_shared<ConsoleDisplay>(20, 14),
           std::make_shared<ConsoleKeyboardController>()) {}

Game::Game(std::shared_ptr<IDisplay> display,
           std::shared_ptr<IInputController> input)
    : glass_(display->height(), display->width()),
      score_(0),
      display_(display),
      input_(input),
      speedup_timer_(30s),
      movedown_timer_(1s) {
  setGamestate<RunningGameState>();
  input_->setGame(this);
  movedown_timer_.start([this] { parseInput(IInputController::Key::DOWN); });
  speedup_timer_.start([this] { speedUp(); });
}

void Game::start() {
  reprintAll();
  input_->startPolling();
}

void Game::parseInput(IInputController::Key key) {
  gamestate_->parseInput(key);
}

bool Game::active() const { return active_; }

void Game::reprint() {
  if (need_reprint_.glass) {
    display_->printGlass(glass_);
  }
  if (need_reprint_.next_figure) {
    display_->printNextFigure(glass_.next_figure());
  }
  if (need_reprint_.figure) {
    display_->printFigure(glass_.figure());
  }
  need_reprint_ = NeedReprint();
}

void Game::reprintAll() {
  display_->printGlass(glass_);
  display_->printScore(score_);
  display_->printFigure(glass_.figure());
  display_->printNextFigure(glass_.next_figure());
}

bool Game::clearRows() {
  bool res = need_clear_rows_;
  if (need_clear_rows_) {
    int cleared_rows = glass_.clearRows();
    if (cleared_rows) {
      score_ += cleared_rows * 100;
      display_->printScore(score_);
      need_reprint_.glass = true;
    }
  }
  need_clear_rows_ = false;
  return res;
}

void Game::moveDown() {
  display_->eraseFigure(glass_.figure());
  bool glued = glass_.figureMoveY(1);
  need_clear_rows_ |= glued;
  need_reprint_.next_figure |= glued;
  need_reprint_.glass |= glued;
  need_reprint_.figure = true;
  if (glued) {  // figure already spawned
    if (glass_.figure()->top() == 0 && glass_.figureIntersects()) {
      active_ = false;
    }
  }
}

void Game::speedUp() {
  movedown_timer_.setDuration(movedown_timer_.duration() * 9 / 10);
}
