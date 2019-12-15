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
  initInput();

  Glass* glass = &game->glass;

  WINDOW* win = newGlassWin();
  printFrame(win);
  printGlass(win, glass);

  WINDOW* info_win = newInfoWin();

  struct timeval speed_amplify_time, move_down_time, current_time;
  gettimeofday(&speed_amplify_time, 0);
  gettimeofday(&move_down_time, 0);

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

    if (gameTryMoveDown(game, &move_down_time, &current_time)) {
      printGlass(win, glass);
    }

    gameTrySpeedUp(game, &speed_amplify_time, &current_time);

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
      int cleared_rows = glassClearRows(glass);
      game->score += cleared_rows * 100;
      printInfo(info_win, game->score);
      printGlass(win, glass);
    }
  }
  endwin();
}

BOOL gameTryMoveDown(Game* game,
                     struct timeval* move_down_time,
                     struct timeval* current_time) {
  if (timeDelta(move_down_time, current_time) >= game->speed) {
    glassFigureMoveY(&game->glass, 1);
    *move_down_time = *current_time;
    return TRUE;
  }
  return FALSE;
}

BOOL gameTrySpeedUp(Game* game,
                    struct timeval* speed_amplify_time,
                    struct timeval* current_time) {
  if (timeDelta(speed_amplify_time, current_time) >=
      GAME_SPEED_AMPLIFY_INTERVAL) {
    game->speed = (int)(game->speed * GAME_SPEED_AMPLIFY_MULTIPLIER);
    *speed_amplify_time = *current_time;
    return TRUE;
  }
  return FALSE;
}

long long timeMicroSeconds(struct timeval* time) {
  return (((long long)time->tv_sec) * SECOND + (long long)(time->tv_usec));
}

long long timeDelta(struct timeval* beg, struct timeval* end) {
  return timeMicroSeconds(end) - timeMicroSeconds(beg);
}
