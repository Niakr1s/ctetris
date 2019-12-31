#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "game.h"
#include "iinputcontroller.h"

class GameState {
 public:
  GameState(Game* game);
  virtual ~GameState() {}

  void parseInput(IInputController::Key key);

 protected:
  Game* game_;

  void defaultParseInput(IInputController::Key key);
  virtual void doParseInput(IInputController::Key key) = 0;
};

class RunningGameState : public GameState {
 public:
  RunningGameState(Game* game);

  void doParseInput(IInputController::Key key) override;
};

class PausedGameState : public GameState {
 public:
  PausedGameState(Game* game);

  void doParseInput(IInputController::Key key) override;
};

#endif  // GAMESTATE_H
