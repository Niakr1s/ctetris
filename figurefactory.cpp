#include "figurefactory.h"

std::shared_ptr<IFigure> FigureFactory::nextFigure() {
  return i_figure_factory_->nextFigure();
}

FigureFactory::FigureFactory(std::shared_ptr<IFigureFactory> iff)
    : i_figure_factory_(iff) {}

template <class FigureFactory_T, typename... Args>
FigureFactory FigureFactory::makeFigureFactory(Args... args) {
  std::shared_ptr<IFigureFactory> iff =
      std::make_shared<IFigureFactory>((FigureFactory_T(args...)));
  return FigureFactory(iff);
}
