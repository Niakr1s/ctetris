#include "keyboardcontroller.h"

#include "platform_specific.h"

KeyboardController::KeyboardController() {
  initscr();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}

IInputController::Key KeyboardController::getKey() {
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
