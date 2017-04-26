#ifndef CONVERTER_H
#define CONVERTER_H

#include <QPointF>
#include <QRectF>

#include "Point.h"
#include "Rectangle.h"

class Converter
{
public:
  static unsigned int toUInt(float value);
  static unsigned int toUInt(double value);

  static QRectF toQRectF(const QPointF& point, float radius = 5.0);
  static QRectF toQRectF(const Point& point, float radius = 5.0);
  static QRectF toQRectF(const Rectangle& rectangle);
  static QPointF toQPointF(const Point& point);
  static Point toPoint(const QPointF& point);
};

#endif // CONVERTER_H
