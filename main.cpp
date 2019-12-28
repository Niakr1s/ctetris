#include <curses.h>

#include "tetrisgame.h"

int main() {
  auto game = TetrisGame();
  game.loop();
  return 0;
}
