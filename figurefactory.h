#ifndef FIGUREFACTORY_H
#define FIGUREFACTORY_H

#include <memory>

#include "ifigurefactory.h"

class FigureFactory {
 public:
  template <class FigureFactory_T, typename... Args>
  static FigureFactory makeFigureFactory(Args...);

  std::shared_ptr<IFigure> nextFigure();

 private:
  FigureFactory(std::shared_ptr<IFigureFactory> iff);

  std::shared_ptr<IFigureFactory> i_figure_factory_;
};

#endif  // FIGUREFACTORY_H
