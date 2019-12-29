#include "game.h"

#include <time.h>

#include <chrono>
#include <thread>

#include "consolekeyboardcontroller.h"

using namespace std::chrono_literals;

Game::Game()
    : Game(std::make_shared<ConsoleDisplay>(20, 14),
           std::make_shared<ConsoleKeyboardController>()) {}

Game::Game(std::shared_ptr<IDisplay> display,
           std::shared_ptr<IInputController> input)
    : glass_(display->height(), display->width()),
      status_(Status::RUNNING),
      score_(0),
      speed_(GAME_DEFAULT_SPEED),
      display_(display),
      input_(input) {}

void Game::loop() {
  display_->printGlass(glass_);
  display_->printScore(score_);
  display_->printFigure(glass_.figure());
  display_->printNextFigure(glass_.next_figure());

  struct timeval speed_amplify_time, move_down_time;
  gettimeofday(&speed_amplify_time, 0);
  gettimeofday(&move_down_time, 0);

  while (status_ != Status::END) {
    if (status_ == Status::RUNNING) {
      runningLoop(speed_amplify_time, move_down_time);
    } else if (status_ == Status::PAUSE) {
      pauseLoop();
    }
  }
}

void Game::parseInput() {
  auto key = input_->getKey();
  if (key != IInputController::Key::NOTHING) {
    display_->eraseFigure(glass_.figure());
    need_reprint_.figure = true;
    need_reprint_.glass = true;
    switch (key) {
      case (IInputController::Key::DOWN):
        tryMoveDown();
        break;
      case (IInputController::Key::LEFT):
        glass_.figureMoveX(-1);
        break;
      case (IInputController::Key::RIGHT):
        glass_.figureMoveX(1);
        break;
      case (IInputController::Key::ROTATE):
        glass_.figureRotateN(1);
        break;
      case (IInputController::Key::QUIT):
        status_ = Status::END;
        break;
      case (IInputController::Key::PAUSE):
        status_ = Status::PAUSE;
        break;
      default:
        break;
    }
  }
}

void Game::runningLoop(struct timeval& speed_amplify_time,
                       struct timeval& move_down_time) {
  if (glass_.figure()->top() == 0 && glass_.figureIntersects()) {
    status_ = Status::END;
    return;
  }

  struct timeval current_time;
  gettimeofday(&current_time, 0);

  tryMoveDown(&move_down_time, &current_time);
  trySpeedUp(&speed_amplify_time, &current_time);

  parseInput();

  clearRows();
  reprint();

  std::this_thread::sleep_for(10ms);
}

void Game::pauseLoop() {
  while (true) {
    switch (input_->getKey()) {
      case (IInputController::Key::PAUSE):
        status_ = Status::RUNNING;
        return;
        break;
      case (IInputController::Key::QUIT):
        status_ = Status::END;
        return;
        break;
      default:
        break;
    }
    std::this_thread::sleep_for(10ms);
  }
}

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

void Game::clearRows() {
  if (need_clear_rows_) {
    int cleared_rows = glass_.clearRows();
    if (cleared_rows) {
      score_ += cleared_rows * 100;
      display_->printScore(score_);
      need_reprint_.glass = true;
    }
  }

  need_clear_rows_ = false;
}

bool Game::tryMoveDown(timeval* move_down_time, timeval* current_time) {
  if (move_down_time == nullptr || current_time == nullptr ||
      timeDelta(move_down_time, current_time) >= speed_) {
    display_->eraseFigure(glass_.figure());
    bool glued = glass_.figureMoveY(1);
    need_clear_rows_ |= glued;
    need_reprint_.next_figure |= glued;
    need_reprint_.glass |= glued;
    need_reprint_.figure = true;
    if (move_down_time != nullptr && current_time != nullptr) {
      *move_down_time = *current_time;
    }
    return true;
  }
  return false;
}

bool Game::trySpeedUp(timeval* speed_amplify_time, timeval* current_time) {
  if (timeDelta(speed_amplify_time, current_time) >=
      GAME_SPEED_AMPLIFY_INTERVAL) {
    speed_ = (int)(speed_ * GAME_SPEED_AMPLIFY_MULTIPLIER);
    *speed_amplify_time = *current_time;
    return true;
  }
  return false;
}

const int Game::SECOND = 1000000LL;
const int Game::GAME_DEFAULT_SPEED = SECOND;
const int Game::GAME_SPEED_AMPLIFY_INTERVAL = SECOND * 30;
const double Game::GAME_SPEED_AMPLIFY_MULTIPLIER = 0.9;

long long timeMicroSeconds(struct timeval* time) {
  return (((long long)time->tv_sec) * Game::SECOND +
          (long long)(time->tv_usec));
}

long long timeDelta(struct timeval* beg, struct timeval* end) {
  return timeMicroSeconds(end) - timeMicroSeconds(beg);
}
