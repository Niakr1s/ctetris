#include "consoledisplaycolored.h"
#include "game.h"
#include "keyboardcontroller.h"

int main() {
  auto input = std::make_shared<KeyboardController>();
  auto display = std::make_shared<ConsoleDisplayColored>(20, 14);
  auto game = Game(display, input);
  game.loop();
  return 0;
}
