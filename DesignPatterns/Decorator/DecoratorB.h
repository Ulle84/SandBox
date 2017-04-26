#ifndef DECORATORB_H
#define DECORATORB_H

#include "Decorator.h"

class DecoratorB : public Decorator
{
public:
  DecoratorB(IComponent* component);
  ~DecoratorB();

  // IComponent
  double operation();
};

#endif // DECORATORB_H
