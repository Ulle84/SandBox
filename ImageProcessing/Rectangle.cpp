#include <math.h>

#include <QDebug>
#include <QLineF>
#include <QPointF>

#include "MathHelper.h"
#include "Rectangle.h"
#include "Converter.h"

Rectangle::Rectangle() :
  m_width(0),
  m_height(0)
{

}

Rectangle::Rectangle(const Point &origin, float width, float height, float angle) :
  m_origin(origin),
  m_width(width),
  m_height(height),
  m_angle(angle)
{

}

Rectangle::Rectangle(const Point &topLeft, const Point &bottomRight) :
  m_origin(topLeft),
  m_angle(0.0)
{
  float dx = bottomRight.x() - topLeft.x();
  float dy = bottomRight.y() - topLeft.y();

  if (dx >= 0.01 && dy >= 0.01)
  {
    m_width = dx;
    m_height = dy;
  }
  else
  {
    m_width = 0;
    m_height = 0;
  }
}

Points Rectangle::getEdgePoints() const
{
  Points edgePoints;

  edgePoints.push_back(m_origin);
  edgePoints.push_back(bottomLeft());
  edgePoints.push_back(bottomRight());
  edgePoints.push_back(topRight());

  return edgePoints;
}

PolyLine Rectangle::toPolyLine() const
{
  PolyLine polyLine;

  polyLine.push_back(m_origin);
  polyLine.push_back(bottomLeft());
  polyLine.push_back(bottomRight());
  polyLine.push_back(topRight());
  polyLine.push_back(m_origin);

  return polyLine;
}

float Rectangle::x() const
{
  return m_origin.x();
}

void Rectangle::setX(float x)
{
  m_origin.setX(x);
}

float Rectangle::y() const
{
  return m_origin.y();
}

void Rectangle::setY(float y)
{
  m_origin.setY(y);
}

float Rectangle::width() const
{
  return m_width;
}

void Rectangle::setWidth(float width)
{
  m_width = width;
}

float Rectangle::height() const
{
  return m_height;
}

void Rectangle::setHeight(float height)
{
  m_height = height;
}

float Rectangle::angle() const
{
  return m_angle;
}

void Rectangle::setAngle(float angle)
{
  m_angle = angle;
}

Point Rectangle::topLeft() const
{
  return m_origin;
}

void Rectangle::setTopLeft(const Point &topLeft)
{
  Point bottomRightOld = bottomRight();
  m_origin = topLeft;
  updateDimensions(topLeft, bottomRightOld);
}

Point Rectangle::topRight() const
{
  return MathHelper::calcEndPoint(m_origin, m_angle, m_width);
}

void Rectangle::setTopRight(const Point &topRight)
{
  Point bottomLeftOld = bottomLeft();
  updateDimensions(topRight, bottomLeftOld);
  m_origin = MathHelper::calcEndPoint(bottomLeftOld, m_angle - 90, m_height);
}

Point Rectangle::bottomLeft() const
{
  return MathHelper::calcEndPoint(m_origin, m_angle + 90, m_height);
}

void Rectangle::setBottomLeft(const Point &bottomLeft)
{
  Point topRightOld = topRight();
  updateDimensions(bottomLeft, topRightOld);
  m_origin = MathHelper::calcEndPoint(topRightOld, m_angle + 180, m_width);
}

Point Rectangle::bottomRight() const
{
  return MathHelper::calcEndPoint(bottomLeft(), m_angle, m_width);
}

void Rectangle::setBottomRight(const Point &bottomRight)
{
  updateDimensions(topLeft(), bottomRight);
}

void Rectangle::moveCenter(const Point &center)
{
  Point p1 = MathHelper::calcEndPoint(center, m_angle + 180, m_width / 2);
  m_origin = MathHelper::calcEndPoint(p1, m_angle - 90, m_height / 2);
}

Rectangle Rectangle::boundingRectangle() const
{
  float xMin = std::numeric_limits<float>::max();
  float xMax = std::numeric_limits<float>::min();

  float yMin = std::numeric_limits<float>::max();
  float yMax = std::numeric_limits<float>::min();

  Points edgePoints = getEdgePoints();

  for (auto it = edgePoints.begin(); it != edgePoints.end(); it++)
  {
    if (it->x() < xMin)
    {
      xMin = it->x();
    }
    if (it->x() > xMax)
    {
      xMax = it->x();
    }
    if (it->y() < yMin)
    {
      yMin = it->y();
    }
    if (it->y() > yMax)
    {
      yMax = it->y();
    }
  }

  return Rectangle(Point(xMin, yMin), Point(xMax, yMax));
}

void Rectangle::updateDimensions(const Point &p1, const Point &p2)
{
  QLineF line1 = QLineF(Converter::toQPointF(p1), Converter::toQPointF(MathHelper::calcEndPoint(p1, m_angle, 100)));
  QLineF line2 = QLineF(Converter::toQPointF(p2), Converter::toQPointF(MathHelper::calcEndPoint(p2, m_angle - 90, 100)));

  QPointF intersection;

  line1.intersect(line2, &intersection); // TODO what if no intersection was found?

  QPointF origin = Converter::toQPointF(p1);

  // TODO negative values?

  QPointF delta1 = intersection - origin;
  QPointF delta2 = intersection - Converter::toQPointF(p2);

  m_width = sqrt(delta1.x() * delta1.x() + delta1.y() * delta1.y());
  m_height = sqrt(delta2.x() * delta2.x() + delta2.y() * delta2.y());
}


