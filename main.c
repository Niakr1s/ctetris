#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#include "display.h"
#include "figure.h"
#include "game.h"
#include "math.h"
#include "pos.h"

int main() {
  Game game = makeGame();
  gameLoop(&game);

  return 0;
}
