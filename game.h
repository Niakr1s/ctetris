#ifndef GAME_H
#define GAME_H

#include <sys/time.h>

#include "constants.h"
#include "glass.h"

static const int SECOND = 1000000LL;
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

Game makeGame(void);

void gameLoop(Game* game);
BOOL gameTryMoveDown(Game* game,
                     struct timeval* move_down_time,
                     struct timeval* current_time);
BOOL gameTrySpeedUp(Game* game,
                    struct timeval* speed_amplify_time,
                    struct timeval* current_time);

long long timeMicroSeconds(struct timeval* time);
long long timeDelta(struct timeval* beg, struct timeval* end);

#endif  // GAME_H
