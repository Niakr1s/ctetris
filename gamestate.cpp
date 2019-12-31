#include "gamestate.h"

GameState::GameState(Game *game) : game_(game) {}

void GameState::parseInput(IInputController::Key key) {
  defaultParseInput(key);
  return doParseInput(key);
}

void GameState::speedUp() { return doSpeedUp(); }

void GameState::defaultParseInput(IInputController::Key key) {
  if (key == IInputController::Key::QUIT) {
    game_->active_ = false;
  }
}

RunningGameState::RunningGameState(Game *game) : GameState(game) {}

void RunningGameState::doParseInput(IInputController::Key key) {
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
    case (IInputController::Key::PAUSE):
      game_->display_->showPauseMenu();
      game_->setGamestate<PausedGameState>();
      game_->need_reprint_.figure = false;
      game_->need_reprint_.glass = false;
      break;
    default:
      break;
  }
  game_->reprintIfNeeded();
}

void RunningGameState::doSpeedUp() {
  game_->movedown_timer_.setDuration(game_->movedown_timer_.duration() * 9 /
                                     10);
}

PausedGameState::PausedGameState(Game *game) : GameState(game) {}

void PausedGameState::doParseInput(IInputController::Key key) {
  switch (key) {
    case (IInputController::Key::PAUSE):
      game_->display_->hidePauseMenu();
      game_->reprintAll();
      game_->setGamestate<RunningGameState>();
      break;
    default:
      break;
  }
}

void PausedGameState::doSpeedUp() {}
