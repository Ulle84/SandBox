#include <limits>

#include "PolyLine.h"
#include "Matrix.h"
#include "Rectangle.h"

PolyLine::PolyLine()
{

}

bool PolyLine::isClosed() const
{
  return front() == back();
}

Rectangle PolyLine::boundingRectangle() const
{
  if (empty())
  {
    // TODO throw exception?
  }

  float xMin;
  float xMax;
  float yMin;
  float yMax;

  getMinMaxValues(xMin, xMax, yMin, yMax);

  return Rectangle(Point(xMin, yMin), Point(yMin, yMax));
}

RunLengthCode PolyLine::toRunLengthCode()
{
  float xMin;
  float xMax;
  float yMin;
  float yMax;

  getMinMaxValues(xMin, xMax, yMin, yMax);

  PolyLine converted = *this;

  for (auto it = converted.begin(); it != converted.end(); it++)
  {
     it->m_x -= xMin;
     it->m_y -= yMin;
  }

  Rectangle rectangle = boundingRectangle();

  StructuringElement structuringElement(rectangle.m_width, rectangle.m_height, false);
  structuringElement.setPolyLine(true, converted);
  structuringElement.fillBackground(false, true);
  structuringElement.invert();
  structuringElement.setPolyLine(true, converted);

  RunLengthCode runLengthCode = structuringElement.getRunLengthCode(true);

  for (auto it = runLengthCode.begin(); it != runLengthCode.end(); it++)
  {
    it->m_startPoint.m_x += xMin;
    it->m_startPoint.m_y += yMin;
  }

  return runLengthCode;
}

void PolyLine::getMinMaxValues(float &xMin, float &xMax, float &yMin, float &yMax) const
{
  xMin = std::numeric_limits<unsigned int>::max();
  xMax = std::numeric_limits<unsigned int>::min();
  yMin = std::numeric_limits<unsigned int>::max();
  yMax = std::numeric_limits<unsigned int>::min();

  for (auto it = begin(); it != end(); it++)
  {
    if (it->m_x < xMin)
    {
      xMin = it->m_x;
    }
    else if (it->m_x > xMax)
    {
      xMax = it->m_x;
    }

    if (it->m_y < yMin)
    {
      yMin = it->m_y;
    }
    else if (it->m_y > yMax)
    {
      yMax = it->m_y;
    }
  }
}

