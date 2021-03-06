#include "consolekeyboardcontroller.h"

#include "platform_specific.h"

ConsoleKeyboardController::ConsoleKeyboardController(Game* game)
    : IInputController(game) {
  initscr();
  keypad(stdscr, TRUE);
}

IInputController::Key ConsoleKeyboardController::getKey() {
  int ch;
  if ((ch = getch()) != ERR) {
    switch (ch) {
      case (KEY_RIGHT):
        return Key::RIGHT;
        break;
      case (KEY_LEFT):
        return Key::LEFT;
        break;
      case (KEY_DOWN):
        return Key::DOWN;
        break;
      case (' '):
        return Key::ROTATE;
        break;
      case ('q'):
      case ('Q'):
        return Key::QUIT;
        break;
      case ('p'):
      case ('P'):
        return Key::PAUSE;
        break;
    }
  }
  return Key::NOTHING;
}
