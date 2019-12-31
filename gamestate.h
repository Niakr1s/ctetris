#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "game.h"
#include "iinputcontroller.h"

class GameState {
 public:
  GameState(Game* game);
  virtual ~GameState() {}

  virtual void parseInput(IInputController::Key key) = 0;

 protected:
  Game* game_;
};

class RunningGameState : public GameState {
 public:
  RunningGameState(Game* game);

  void parseInput(IInputController::Key key) override;
};

class PausedGameState : public GameState {
 public:
  PausedGameState(Game* game);

  void parseInput(IInputController::Key key) override;
};

#endif  // GAMESTATE_H
