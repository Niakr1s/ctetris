#ifndef GAME_H
#define GAME_H

#include <sys/time.h>

#include "consoledisplay.h"
#include "glass.h"
#include "iinputcontroller.h"
#include "timer.h"

class Game {
 public:
  enum class Status { RUNNING, PAUSE, END };

  struct NeedReprint {
    bool glass = false, next_figure = false, figure = false;
  };

  Game();
  Game(std::shared_ptr<IDisplay> display,
       std::shared_ptr<IInputController> input);

  void start();

  Status status() const;
  void parseInput(IInputController::Key key);

 private:
  Glass glass_;
  Status status_;
  int score_;
  int speed_;
  std::shared_ptr<IDisplay> display_;
  std::shared_ptr<IInputController> input_;
  NeedReprint need_reprint_;
  bool need_clear_rows_ = false;
  Timer speedup_timer_, movedown_timer_;

  void runningLoop();
  void pauseLoop();

  void reprint();
  void reprintAll();
  bool clearRows();

  void moveDown();
  void speedUp();
};

#endif  // GAME_H
