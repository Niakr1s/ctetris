#include "gamestate.h"

GameState::GameState(Game *game) : game_(game) {}

RunningGameState::RunningGameState(Game *game) : GameState(game) {}

void RunningGameState::parseInput(IInputController::Key key) {
  game_->display_->eraseFigure(game_->glass_.figure());
  game_->need_reprint_.figure = true;
  game_->need_reprint_.glass = true;
  switch (key) {
    case (IInputController::Key::DOWN):
      game_->moveDown();
      game_->clearRows();
      break;
    case (IInputController::Key::LEFT):
      game_->glass_.figureMoveX(-1);
      break;
    case (IInputController::Key::RIGHT):
      game_->glass_.figureMoveX(1);
      break;
    case (IInputController::Key::ROTATE):
      game_->glass_.figureRotateN(1);
      break;
    case (IInputController::Key::QUIT):
      game_->active_ = false;
      break;
    case (IInputController::Key::PAUSE):
      game_->setGamestate<PausedGameState>();
      break;
    default:
      break;
  }
  game_->reprint();
}

PausedGameState::PausedGameState(Game *game) : GameState(game) {}

void PausedGameState::parseInput(IInputController::Key key) {
  switch (key) {
    case (IInputController::Key::QUIT):
      game_->active_ = false;
      break;
    case (IInputController::Key::PAUSE):
      game_->setGamestate<RunningGameState>();
      break;
    default:
      break;
  }
}
