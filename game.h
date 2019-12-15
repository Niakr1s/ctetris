#ifndef GAME_H
#define GAME_H

#include <sys/time.h>

#include "constants.h"
#include "glass.h"

static const int SECOND = 1000000;
static const int GAME_DEFAULT_SPEED = SECOND;
static const int GAME_SPEED_AMPLIFY_INTERVAL = SECOND * 1;
static const double GAME_SPEED_AMPLIFY_MULTIPLIER = 0.9;

enum {
  GAME_RUNNING,
  GAME_END,
};

typedef struct Game {
  int status;
  int score;
  Glass glass;
  int speed;
} Game;

Game makeGame();

void gameLoop(Game* game);

long long timeMicroSeconds(struct timeval* time);
long long timeDelta(struct timeval* beg, struct timeval* end);

#endif  // GAME_H
