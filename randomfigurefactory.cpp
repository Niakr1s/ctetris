#include "randomfigurefactory.h"

#include "rnd.h"
#include "standardfigure.h"

template <typename Figure_T>
RandomFigureFactory<Figure_T>::RandomFigureFactory() {
  if (!random_initiated_) {
    randomInit();
    random_initiated_ = true;
  }
}

template <typename Figure_T>
std::shared_ptr<IFigure> RandomFigureFactory<Figure_T>::nextFigure() {
  int rnd_figure_type =
      randomZeroToMax(static_cast<int>(IFigure::Type::FIGURE_MAX));
  std::shared_ptr<IFigure> res =
      std::make_shared<Figure_T>(IFigure::Type(rnd_figure_type));
  int rnd_angle = randomZeroToMax(res->maxAngle());
  res->rotateN(rnd_angle);
  return res;
}

template <typename Figure_T>
bool RandomFigureFactory<Figure_T>::random_initiated_ = false;
