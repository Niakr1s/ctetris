#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "iinputcontroller.h"

class ConsoleKeyboardController : public IInputController {
 public:
  ConsoleKeyboardController();

  Key getKey() override;
};

#endif  // KEYBOARDCONTROLLER_H
