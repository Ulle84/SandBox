#ifndef FREEMANCODE_H
#define FREEMANCODE_H

#include <list>

#include "Point.h"

class FreemanCode
{
public:
  FreemanCode();

  Point m_startPoint; // TODO really public?
  std::list<unsigned char> m_directions;

  void setStartPoint(const Point& startPoint);
  void setDirections(const std::list<unsigned char>& directions);
};

#endif // FREEMANCODE_H
