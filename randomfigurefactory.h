#ifndef RANDOMFIGUREFACTORY_H
#define RANDOMFIGUREFACTORY_H

#include "ifigurefactory.h"
#include "rnd.h"

/* please, to RandomFigureFactory work with your IFigure child,
 * provide it with enum class Type and last element of it should be MAX
 *
 * example:
 * enum class Type: int {
 * ...
 * MAX
 * } */

template <typename Figure_T>
class RandomFigureFactory : public IFigureFactory {
 public:
  RandomFigureFactory() {
    if (!random_initiated_) {
      randomInit();
      random_initiated_ = true;
    }
  }

  std::shared_ptr<IFigure> nextFigure() override {
    int rnd_figure_type =
        randomZeroToMax(static_cast<int>(Figure_T::Type::MAX));
    std::shared_ptr<IFigure> res = std::make_shared<Figure_T>(
        static_cast<typename Figure_T::Type>(rnd_figure_type));
    int rnd_angle = randomZeroToMax(res->maxAngle());
    res->rotateN(rnd_angle);
    return res;
  }

 private:
  static bool random_initiated_;
};

template <typename Figure_T>
bool RandomFigureFactory<Figure_T>::random_initiated_ = false;

#endif  // RANDOMFIGUREFACTORY_H
