#include "GeometryCodeGenerator.h"

GeometryCodeGenerator::GeometryCodeGenerator()
{
}

QString GeometryCodeGenerator::generate(const QPointF &point, bool generateName)
{
  return QString("Point%1(%2, %3)").arg(generateName ? " point" : "").arg(QString::number(point.x())).arg(point.y());
}

QString GeometryCodeGenerator::generate(const QLineF &line, bool generateName)
{
  return QString("Line%1(%2, %3)").arg(generateName ? " line" : "").arg(generate(line.p1(), false)).arg(generate(line.p2(), false));
}

QString GeometryCodeGenerator::generate(const QRectF &rect, bool generateName, bool interpretAsCirlce)
{
  if (interpretAsCirlce)
  {
    return QString("Circle%1(%2, %3)").arg(generateName ? " circle" : "").arg(generate(rect.center(), false)).arg(QString::number(rect.center().y() - rect.y()));
  }
  else
  {
    return QString("Rectangle%1(%2, %3, %4)").arg(generateName ? " rectangle" : "").arg(generate(rect.topLeft(), false)).arg(QString::number(rect.width())).arg(QString::number(rect.height()));
  }
}
