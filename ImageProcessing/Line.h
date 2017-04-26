#ifndef LINE_H
#define LINE_H

#include "Point.h"

class Line
{
public:
  Line(const Point& startPoint, const Point& endPoint);
  Line(const Point& startPoint, float angle, float lenght);

  Point getStartPoint() const;
  Point getEndPoint() const;
  float angle() const;

  Points getPointsAlongLine() const;

private:
  Point m_startPoint;
  Point m_endPoint;
  float m_angle;
  float m_lenght;
};

#endif // LINE_H
