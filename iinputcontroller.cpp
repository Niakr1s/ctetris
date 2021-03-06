#include "iinputcontroller.h"

#include <thread>

#include "game.h"

void IInputController::startPolling() {
  while (true) {
    auto key = getKey();
    if (key == Key::NOTHING) {
      continue;
    }
    game_->parseInput(key);
  }
}

void IInputController::setGame(Game *game) { game_ = game; }
