#include "Decorator.h"

Decorator::Decorator(IComponent *component)
  : mComponent(component)
{
}

Decorator::~Decorator()
{
}

double Decorator::operation()
{
  return mComponent->operation();
}
