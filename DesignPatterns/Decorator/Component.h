#ifndef COMPONENT_H
#define COMPONENT_H

#include "IComponent.h"

class Component : public IComponent
{
public:
  Component();
  ~Component();

  // IComponent
  double operation();
};

#endif // COMPONENT_H
