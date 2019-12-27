#ifndef IFIGUREFACTORY_H
#define IFIGUREFACTORY_H

#include <memory>

#include "ifigure.h"

class IFigureFactory {
 public:
  virtual ~IFigureFactory() = default;

  virtual std::shared_ptr<IFigure> nextFigure() = 0;
};

#endif  // IFIGUREFACTORY_H
