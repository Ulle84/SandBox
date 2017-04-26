#ifndef RECTANGLEROTATED_H
#define RECTANGLEROTATED_H

#include <QGraphicsItem>

#include "Rectangle.h"

// TODO rename to GraphicsRectangle?

class RectangleRotated : public QGraphicsItem
{
public:
  RectangleRotated(QPen* pen, QBrush* brush);
  ~RectangleRotated();

  enum { Type = UserType + 1 };
  int type() const {return Type;}

  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  QPainterPath shape() const;

  Rectangle rectangle();
  void setRectangle(const Rectangle& rectangle);

private:
  Rectangle m_rectangle;
  QPen* m_pen;
  QBrush* m_brush;
};

#endif // RECTANGLEROTATED_H
