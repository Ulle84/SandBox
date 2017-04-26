#ifndef GEOMETRYCODEGENERATOR_H
#define GEOMETRYCODEGENERATOR_H

#include <QLineF>
#include <QPointF>
#include <QRectF>
#include <QString>

class GeometryCodeGenerator
{
public:
  GeometryCodeGenerator();

  static QString generate(const QPointF& point, bool generateName = true);
  static QString generate(const QLineF& line, bool generateName = true);
  static QString generate(const QRectF& rect, bool generateName = true, bool interpretAsCirlce = false);

};

#endif // GEOMETRYCODEGENERATOR_H
