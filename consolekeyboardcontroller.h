#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "iinputcontroller.h"

class ConsoleKeyboardController : public IInputController {
 public:
  ConsoleKeyboardController(Game *game = nullptr);

  Key getKey() override;
};

#endif  // KEYBOARDCONTROLLER_H
