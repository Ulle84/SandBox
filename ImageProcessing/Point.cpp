#include "Point.h"

Point::Point() :
  m_x(0.0),
  m_y(0.0)
{

}

Point::Point(float x, float y) :
  m_x(x),
  m_y(y)
{
}

bool Point::operator==(const Point &rhs) const
{
  return m_x == rhs.m_x && m_y == rhs.m_y;
}

float Point::x() const
{
  return m_x;
}

void Point::setX(float x)
{
  m_x = x;
}

float Point::y() const
{
  return m_y;
}

void Point::setY(float y)
{
  m_y = y;
}

