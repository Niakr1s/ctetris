#ifndef GAME_H
#define GAME_H

#include <sys/time.h>

#include "consoledisplay.h"
#include "glass.h"
#include "iinputcontroller.h"
#include "timer.h"

class GameState;

class Game {
  friend class GameState;
  friend class RunningGameState;
  friend class PausedGameState;

 public:
  struct NeedReprint {
    bool glass = false, next_figure = false, figure = false;
  };

  Game();
  Game(std::shared_ptr<IDisplay> display,
       std::shared_ptr<IInputController> input);

  void start();

  void parseInput(IInputController::Key key);

  bool active() const;

 private:
  std::shared_ptr<GameState> gamestate_;
  Glass glass_;
  bool active_ = true;
  int score_;
  int speed_;
  std::shared_ptr<IDisplay> display_;
  std::shared_ptr<IInputController> input_;
  NeedReprint need_reprint_;
  bool need_clear_rows_ = false;
  Timer speedup_timer_, movedown_timer_;

  void reprintIfNeeded();
  void reprintAll();
  bool clearRows();

  void moveDown();
  void speedUp();

  template <class T>
  void setGamestate() {
    gamestate_ = std::make_shared<T>(this);
  }
};

#endif  // GAME_H
