#ifndef IINPUTCONTROLLER_H
#define IINPUTCONTROLLER_H

class IInputController {
 public:
  enum class Key {
    RIGHT,
    LEFT,
    DOWN,
    ROTATE,
    QUIT,
    PAUSE,
    NOTHING,
  };

  virtual Key getKey() = 0;
};

#endif  // IINPUTCONTROLLER_H
