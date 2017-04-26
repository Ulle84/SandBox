#ifndef MATHHELPER_H
#define MATHHELPER_H

#include "Point.h"

const double PI = 3.14159265359;
const double HalfPI = 1.57079632679;

class MathHelper
{
public:
  static double deg(double angleInRad);
  static double rad(double angleInDeg);
  static Point calcEndPoint(const Point& startPoint, float angle, float length);
  static void calcAngleAndLength(const Point& startPoint, const Point& endPoint, float& angle, float& length);
  static bool isBetween(float min, float value, float max);
};

#endif // MATHHELPER_H
