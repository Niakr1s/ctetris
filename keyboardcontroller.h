#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "iinputcontroller.h"

class KeyboardController : public IInputController {
 public:
  KeyboardController();

  Key getKey() override;
};

#endif  // KEYBOARDCONTROLLER_H
