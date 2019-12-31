#include "iinputcontroller.h"

#include <thread>

#include "game.h"

void IInputController::startPolling() {
  std::thread([this] {
    while (game_->status() != Game::Status::END) {
      auto key = getKey();
      if (key == Key::NOTHING) {
        continue;
      }
      game_->parseInput(key);
    }
  }).detach();
}

void IInputController::setGame(Game *game) { game_ = game; }
