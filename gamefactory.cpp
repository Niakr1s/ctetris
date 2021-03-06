#include "gamefactory.h"

#include "consoledisplay.h"
#include "consoledisplaycolored.h"
#include "consolekeyboardcontroller.h"
#include "cstring"

Game* GameFactory::makeGame(const Settings& settings) {
  std::shared_ptr<IDisplay> display;
  if (settings.display.empty()) {
    display = defaultDisplay();
  } else if (settings.display == "console") {
    if (settings.console_colored) {
      display = std::make_shared<ConsoleDisplayColored>(HEIGHT, WIDTH);
    } else {
      display = std::make_shared<ConsoleDisplay>(HEIGHT, WIDTH);
    }
  } else {
    throw(std::invalid_argument("GameFactory::makeGame: wrong display"));
  }

  std::shared_ptr<IInputController> input;
  if (settings.input.empty()) {
    input = defaultInput();
  } else if (settings.display == "console") {
    if (settings.input == "keyboard") {
      input = std::make_shared<ConsoleKeyboardController>();
    }
  } else {
    throw(std::invalid_argument("GameFactory::makeGame: wrong input"));
  }

  Game* game = new Game(display, input);
  return game;
}

std::shared_ptr<IInputController> GameFactory::defaultInput() {
  return std::make_shared<ConsoleKeyboardController>();
}

std::shared_ptr<IDisplay> GameFactory::defaultDisplay() {
  return std::make_shared<ConsoleDisplay>(HEIGHT, WIDTH);
}

const int GameFactory::HEIGHT = 20;
const int GameFactory::WIDTH = 14;
