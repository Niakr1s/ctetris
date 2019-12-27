#ifndef RANDOMFIGUREFACTORY_H
#define RANDOMFIGUREFACTORY_H

#include "ifigurefactory.h"

template <typename Figure_T>
class RandomFigureFactory : public IFigureFactory {
 public:
  RandomFigureFactory();

  // IFigureFactory interface
 public:
  std::shared_ptr<IFigure> nextFigure();

 private:
  static bool random_initiated_;
};

#endif  // RANDOMFIGUREFACTORY_H
