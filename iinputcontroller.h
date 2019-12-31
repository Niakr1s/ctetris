#ifndef IINPUTCONTROLLER_H
#define IINPUTCONTROLLER_H

class Game;

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

  IInputController(Game* game = nullptr) : game_(game) {}
  virtual ~IInputController() {}

  void startPolling();
  void setGame(Game* game);

  virtual Key getKey() = 0;

 private:
  Game* game_;
};

#endif  // IINPUTCONTROLLER_H
