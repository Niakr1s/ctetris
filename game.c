#include "game.h"

#include "display.h"

Game makeGame() {
  Game res;
  res.status = GAME_RUNNING;
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

  int ch;
  while (game->status == GAME_RUNNING) {
    if (!game->glass.figure) {
      if (!glassSpawnFigure(glass, FIGURE_ZIGZAG)) {
        game->status = GAME_END;
        continue;
      }
      printGlass(win, glass);
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
      printGlass(win, glass);

      if (glass->figure) {
        move(0, 0);
        printw("%d, %d, %d", figureLeft(glass->figure),
               figureRight(glass->figure), figureBottom(glass->figure));
      }
    }
  }
  endwin();
}
