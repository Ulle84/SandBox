#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"

class Circle
{
public:
  Circle();
  Circle(const Point& center, unsigned int radius);

  Point m_center;
  unsigned int m_radius;
};

#endif // CIRCLE_H
