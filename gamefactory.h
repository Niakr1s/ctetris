#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include <string>

#include "game.h"

class GameFactory {
 public:
  struct Settings {
    std::string display = "console", input = "keyboard";
    bool console_colored = false;
  };

  static Game *makeGame(const Settings &settings);

  static const int WIDTH, HEIGHT;

 private:
  static std::shared_ptr<IInputController> defaultInput();
  static std::shared_ptr<IDisplay> defaultDisplay();
};

#endif  // GAMEFACTORY_H
