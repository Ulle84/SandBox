#include <iostream>

#include "MathHelper.h"

#include "Line.h"

Line::Line(const Point& startPoint, const Point& endPoint) :
  m_startPoint(startPoint),
  m_endPoint(endPoint)
{
  MathHelper::calcAngleAndLength(m_startPoint, m_endPoint, m_angle, m_lenght);
}

Line::Line(const Point& startPoint, float angle, float lenght) :
  m_startPoint(startPoint),
  m_angle(angle),
  m_lenght(lenght)
{
  m_endPoint = MathHelper::calcEndPoint(m_startPoint, m_angle, m_lenght);
}

Point Line::getStartPoint() const
{
  return m_startPoint;
}

Point Line::getEndPoint() const
{
  return m_endPoint;
}

float Line::angle() const
{
  return m_angle;
}

Points Line::getPointsAlongLine() const
{
  // code below copied partially from
  // https://de.wikipedia.org/wiki/Bresenham-Algorithmus#Kompakte_Variante

  int x0 = m_startPoint.m_x;
  int y0 = m_startPoint.m_y;
  int x1 = m_endPoint.m_x;
  int y1 = m_endPoint.m_y;

  int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2; /* error value e_xy */

  Points points;
  while(1){
    points.push_back(Point(x0, y0));
    if (x0==x1 && y0==y1) break;
    e2 = 2*err;
    if (e2 > dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 < dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }

  return points;
}

