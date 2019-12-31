#include "iinputcontroller.h"

#include <thread>

#include "game.h"

void IInputController::startPolling() {
  while (game_->status() != Game::Status::END) {
    auto key = getKey();
    if (key == Key::NOTHING) {
      continue;
    }
    game_->parseInput(key);
  }
}

void IInputController::setGame(Game *game) { game_ = game; }
