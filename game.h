#ifndef GAME_H
#define GAME_H

#include "constants.h"
#include "glass.h"

enum {
  GAME_RUNNING,
  GAME_END,
};

typedef struct Game {
  int status;
  int score;
  Glass glass;
} Game;

Game makeGame();

void gameLoop(Game* game);

#endif  // GAME_H
