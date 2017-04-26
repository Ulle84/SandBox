#include <iostream>
#include <math.h>

#include "MathHelper.h"

double MathHelper::deg(double angleInRad)
{
  return angleInRad * 180.0 / PI;
}

double MathHelper::rad(double angleInDeg)
{
  return angleInDeg * PI / 180.0;
}

Point MathHelper::calcEndPoint(const Point &startPoint, float angle, float length)
{
  Point endPoint;

  endPoint.setX(startPoint.x() + length * cos(rad(angle)));
  endPoint.setY(startPoint.y()+ length * sin(rad(angle)));

  return endPoint;
}

void MathHelper::calcAngleAndLength(const Point &startPoint, const Point &endPoint, float &angle, float &length)
{
  float x = endPoint.x() - startPoint.x();
  float y = endPoint.y() - startPoint.y();

  length = sqrt(x * x + y * y);
  angle = deg(atan2(y, x));
}

bool MathHelper::isBetween(float min, float value, float max)
{
  if (value < min)
  {
    return false;
  }
  if (value > max)
  {
    return false;
  }
  return true;
}
