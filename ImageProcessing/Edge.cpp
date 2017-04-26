#include "Edge.h"

Edge::Edge(const Point& position, float direction, float strength) :
  m_position(position),
  m_direction(direction),
  m_strength(strength)
{
}

Point Edge::getPosition()
{
  return m_position;
}
