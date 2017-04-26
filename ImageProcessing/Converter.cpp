#include <iostream>

#include <QDebug>

#include "Converter.h"


unsigned int Converter::toUInt(float value)
{
  if (value < 0.0)
  {
    return 0;
  }

  unsigned int result = value + 0.5;

  return result;
}

unsigned int Converter::toUInt(double value)
{
  if (value < 0.0)
  {
    return 0;
  }

  unsigned int result = value + 0.5;

  return result;
}

QRectF Converter::toQRectF(const QPointF& point, float radius)
{
  QPointF offset(radius, radius);
  return QRectF(point - offset, point + offset);
}

QRectF Converter::toQRectF(const Point &point, float radius)
{
  QPointF offset(radius, radius);
  return QRectF(toQPointF(point) - offset, toQPointF(point) + offset);
}

QRectF Converter::toQRectF(const Rectangle &rectangle)
{
  return QRectF(Converter::toQPointF(rectangle.topLeft()), Converter::toQPointF(rectangle.bottomRight()));
}

QPointF Converter::toQPointF(const Point &point)
{
  return QPointF(point.x(), point.y());
}

Point Converter::toPoint(const QPointF &point)
{
  return Point(point.x(), point.y());
}
