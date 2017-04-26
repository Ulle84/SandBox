#include "DecoratorA.h"

DecoratorA::DecoratorA(IComponent *component)
  : Decorator(component)
{
}

DecoratorA::~DecoratorA()
{
}

double DecoratorA::operation()
{
  return Decorator::operation() / 2;
}
