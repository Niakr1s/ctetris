#include "game.h"

#include <threads.h>
#include <time.h>

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

  WINDOW* info_win = newInfoWin();
  printInfo(info_win, game->score);

  WINDOW* next_figure_win = newNextFigureWin();
  printNextFigure(next_figure_win, glass->next_figure);

  struct timeval speed_amplify_time, move_down_time, current_time;
  gettimeofday(&speed_amplify_time, 0);
  gettimeofday(&move_down_time, 0);

  int ch;
  while (game->status == GAME_RUNNING) {
    BOOL need_reprint_glass = FALSE;
    BOOL need_clear_rows = FALSE;

    if (!game->glass.figure) {
      if (!glassSpawnFigure(glass)) {
        game->status = GAME_END;
        continue;
      } else {
        printNextFigure(next_figure_win, glass->next_figure);
      }
      printGlass(win, glass);
    }

    gettimeofday(&current_time, 0);
    if (gameTryMoveDown(game, &move_down_time, &current_time)) {
      need_reprint_glass = TRUE;
      need_clear_rows = TRUE;
    }
    gameTrySpeedUp(game, &speed_amplify_time, &current_time);

    if ((ch = getch()) != ERR) {
      need_reprint_glass = TRUE;
      switch (ch) {
        case (KEY_RIGHT):
          glassFigureMoveX(glass, 1);
          break;
        case (KEY_LEFT):
          glassFigureMoveX(glass, -1);
          break;
        case (KEY_DOWN):
          glassFigureMoveY(glass, 1);
          need_clear_rows = TRUE;
          break;
        case (KEY_UP):
          glassFigureMoveY(glass, -1);
          break;
        case (' '):
          glassFigureRotateN(glass, 1);
          break;
        case ('q'):
        case ('Q'):
          game->status = GAME_END;
          break;
      }
    }
    if (need_clear_rows) {
      int cleared_rows = glassClearRows(&game->glass);
      if (cleared_rows) {
        game->score += cleared_rows * 100;
        printInfo(info_win, game->score);
        need_reprint_glass = TRUE;
      }
    }
    if (need_reprint_glass) {
      printGlass(win, glass);
    }

    thrd_sleep(&(struct timespec){.tv_nsec = (int)(SECOND * 0.1)}, 0);
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
