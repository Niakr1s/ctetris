#ifndef GAME_H
#define GAME_H

#include <sys/time.h>

#include "display.h"
#include "glass.h"
#include "igame.h"
#include "iinputcontroller.h"

class Game : public IGame {
 public:
  enum class Status { RUNNING, PAUSE, END };

  static const int SECOND;
  static const int GAME_DEFAULT_SPEED;
  static const int GAME_SPEED_AMPLIFY_INTERVAL;
  static const double GAME_SPEED_AMPLIFY_MULTIPLIER;

  struct NeedReprint {
    bool glass = false, next_figure = false, figure = false;
  };

  Game();

  void loop() override;

 private:
  Glass glass_;
  Status status_;
  int score_;
  int speed_;
  std::shared_ptr<IDisplay> display_;
  std::shared_ptr<IInputController> input_;
  NeedReprint need_reprint_;
  bool need_clear_rows_ = false;

  void parseInput();
  void runningLoop(timeval& speed_amplify_time, timeval& move_down_time);
  void pauseLoop();

  void reprint();
  void clearRows();

  bool tryMoveDown(struct timeval* move_down_time = nullptr,
                   struct timeval* current_time = nullptr);
  bool trySpeedUp(struct timeval* speed_amplify_time,
                  struct timeval* current_time);
};

long long timeMicroSeconds(struct timeval* time);
long long timeDelta(struct timeval* beg, struct timeval* end);

#endif  // GAME_H
