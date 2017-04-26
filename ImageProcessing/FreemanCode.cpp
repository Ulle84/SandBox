#include "FreemanCode.h"

FreemanCode::FreemanCode()
{

}

void FreemanCode::setStartPoint(const Point &startPoint)
{
  m_startPoint = startPoint;
}

void FreemanCode::setDirections(const std::list<unsigned char> &directions)
{
  m_directions = directions;
}
