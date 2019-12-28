#include <curses.h>

#include "game.h"

int main() {
  auto game = TetrisGame();
  game.loop();
  return 0;
}
