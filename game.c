#include "game.h"

#include "display.h"

Game makeGame(void) {
  Game res;
  res.status = GAME_RUNNING;
  res.speed = GAME_DEFAULT_SPEED;
  res.score = 0;
  res.glass = makeGlass();
  return res;
}

void gameLoop(Game* game) {
  initscr();

  WINDOW* win = newGlassWin();
  Glass* glass = &game->glass;

  initInput();
  printFrame(win);

  printGlass(win, glass);

  struct timeval speed_amplify_time, start_time, current_time;
  gettimeofday(&speed_amplify_time, 0);
  gettimeofday(&start_time, 0);

  int ch;
  while (game->status == GAME_RUNNING) {
    if (!game->glass.figure) {
      if (!glassSpawnRandomFigure(glass)) {
        game->status = GAME_END;
        continue;
      }
      printGlass(win, glass);
    }

    gettimeofday(&current_time, 0);

    // moving down
    if (timeDelta(&start_time, &current_time) >= game->speed) {
      glassFigureMoveY(glass, 1);
      start_time = current_time;
      printGlass(win, glass);
    }

    // speed up
    if (timeDelta(&speed_amplify_time, &current_time) >=
        GAME_SPEED_AMPLIFY_INTERVAL) {
      game->speed = (int)(game->speed * GAME_SPEED_AMPLIFY_MULTIPLIER);
      speed_amplify_time = current_time;
    }

    if ((ch = getch()) != ERR) {
      switch (ch) {
        case (KEY_RIGHT):
          glassFigureMoveX(glass, 1);
          break;
        case (KEY_LEFT):
          glassFigureMoveX(glass, -1);
          break;
        case (KEY_DOWN):
          glassFigureMoveY(glass, 1);
          break;
        case (KEY_UP):
          glassFigureMoveY(glass, -1);
          break;
        case (' '):
          rotateRight(glass->figure);
          break;
        case ('q'):
        case ('Q'):
          game->status = GAME_END;
          break;
      }
      glassClearRows(glass);
      printGlass(win, glass);
    }
  }
  endwin();
}

long long timeMicroSeconds(struct timeval* time) {
  return (((long long)time->tv_sec) * SECOND + (long long)(time->tv_usec));
}

long long timeDelta(struct timeval* beg, struct timeval* end) {
  return timeMicroSeconds(end) - timeMicroSeconds(beg);
}
