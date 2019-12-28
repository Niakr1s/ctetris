#include "tetrisgame.h"

#include <time.h>

#include <chrono>
#include <thread>

TetrisGame::TetrisGame()
    : glass_(),
      status_(Status::RUNNING),
      score_(0),
      speed_(GAME_DEFAULT_SPEED),
      display_(std::make_shared<Display>(glass_.height(), glass_.width())) {}

void TetrisGame::loop() {
  display_->printGlass(glass_);
  display_->printScore(score_);
  display_->printNextFigure(glass_.next_figure());

  struct timeval speed_amplify_time, move_down_time, current_time;
  gettimeofday(&speed_amplify_time, 0);
  gettimeofday(&move_down_time, 0);

  int ch;
  while (status_ == Status::RUNNING) {
    if (glass_.figureIntersects()) {
      status_ = Status::END;
      continue;
    }
    gettimeofday(&current_time, 0);
    tryMoveDown(&move_down_time, &current_time);
    trySpeedUp(&speed_amplify_time, &current_time);

    if ((ch = getch()) != ERR) {
      need_reprint_glass_ = TRUE;
      switch (ch) {
        case (KEY_RIGHT):
          glass_.figureMoveX(1);
          break;
        case (KEY_LEFT):
          glass_.figureMoveX(-1);
          break;
        case (KEY_DOWN):
          tryMoveDown();
          break;
        case (' '):
          glass_.figureRotateN(1);
          break;
        case ('q'):
        case ('Q'):
          status_ = Status::END;
          break;
      }
    }
    if (need_clear_rows_) {
      int cleared_rows = glass_.clearRows();
      if (cleared_rows) {
        score_ += cleared_rows * 100;
        display_->printScore(score_);
        need_reprint_glass_ = true;
      }
    }
    if (need_reprint_glass_) {
      display_->printGlass(glass_);
    }
    if (need_reprint_next_figure_) {
      display_->printNextFigure(glass_.next_figure());
    }
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(10ms);
  }
}

bool TetrisGame::tryMoveDown(timeval* move_down_time, timeval* current_time) {
  if (move_down_time == nullptr || current_time == nullptr ||
      timeDelta(move_down_time, current_time) >= speed_) {
    bool glued = glass_.figureMoveY(1);
    need_clear_rows_ |= glued;
    need_reprint_next_figure_ |= glued;
    need_reprint_glass_ = true;
    if (move_down_time != nullptr && current_time != nullptr) {
      *move_down_time = *current_time;
    }
    return true;
  }
  return false;
}

bool TetrisGame::trySpeedUp(timeval* speed_amplify_time,
                            timeval* current_time) {
  if (timeDelta(speed_amplify_time, current_time) >=
      GAME_SPEED_AMPLIFY_INTERVAL) {
    speed_ = (int)(speed_ * GAME_SPEED_AMPLIFY_MULTIPLIER);
    *speed_amplify_time = *current_time;
    return true;
  }
  return false;
}

const int TetrisGame::SECOND = 1000000LL;
const int TetrisGame::GAME_DEFAULT_SPEED = SECOND;
const int TetrisGame::GAME_SPEED_AMPLIFY_INTERVAL = SECOND * 30;
const double TetrisGame::GAME_SPEED_AMPLIFY_MULTIPLIER = 0.9;

long long timeMicroSeconds(struct timeval* time) {
  return (((long long)time->tv_sec) * TetrisGame::SECOND +
          (long long)(time->tv_usec));
}

long long timeDelta(struct timeval* beg, struct timeval* end) {
  return timeMicroSeconds(end) - timeMicroSeconds(beg);
}
