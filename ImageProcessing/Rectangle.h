#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <list>

#include "Point.h"
#include "PolyLine.h"

class Rectangle
{
public:
  Rectangle();
  Rectangle(const Point& origin, float width, float height, float angle = 0.0);
  Rectangle(const Point& topLeft, const Point& bottomRight);
  //Rectangle(const Line& line, unsigned int height); // TODO

  Points getEdgePoints() const;
  PolyLine toPolyLine() const;

  float x() const;
  void setX(float x);

  float y() const;
  void setY(float y);

  float width() const;
  void setWidth(float width);

  float height() const;
  void setHeight(float height);

  float angle() const;
  void setAngle(float angle);

  Point topLeft() const;
  void setTopLeft(const Point& topLeft);

  Point topRight() const;
  void setTopRight(const Point& topRight);

  Point bottomLeft() const;
  void setBottomLeft(const Point& bottomLeft);

  Point bottomRight() const;
  void setBottomRight(const Point& bottomRight);

  void moveCenter(const Point& center);

  Rectangle boundingRectangle() const;

  Point m_origin; // TODO -> private
  float m_width;
  float m_height;
  float m_angle;

private:
  void updateDimensions(const Point& p1, const Point& p2);
};

#endif // RECTANGLE_H
