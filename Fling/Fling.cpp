#include "Fling.h"
#include <iostream>

Fling::Fling()
{
  x = 0;
  y = 0;
}

Fling::Fling(unsigned int x, unsigned int y)
{
  this->x = x;
  this->y = y;
}


void Fling::print()
{
  std::cout << "Fling x: " << x << " y: " << y << std::endl;
}

void Fling::setX(unsigned int x)
{
  this->x = x;
}

void Fling::setY(unsigned int y)
{
  this->y = y;
}
