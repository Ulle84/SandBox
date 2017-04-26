#ifndef POLYLINE_H
#define POLYLINE_H

#include <list>

#include "Point.h"
#include "RunLengthCode.h"

class Rectangle;

class PolyLine : public std::list<Point>
{
public:
  PolyLine();

  bool isClosed() const;

  Rectangle boundingRectangle() const;
  RunLengthCode toRunLengthCode();

private:
  void getMinMaxValues(float& xMin, float& xMax, float& yMin, float& yMax) const;
};

#endif // POLYLINE_H
