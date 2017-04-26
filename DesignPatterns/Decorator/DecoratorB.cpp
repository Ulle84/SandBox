#include "DecoratorB.h"

DecoratorB::DecoratorB(IComponent *component)
: Decorator(component)
{
}

DecoratorB::~DecoratorB()
{
}

double DecoratorB::operation()
{
  return Decorator::operation() * 5;
}
