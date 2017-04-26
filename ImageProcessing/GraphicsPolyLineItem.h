#ifndef GRAPHICSPOLYLINEITEM_H
#define GRAPHICSPOLYLINEITEM_H

#include <QGraphicsItem>

#include "PolyLine.h"

class GraphicsPolyLineItem : public QGraphicsItem
{
public:
  GraphicsPolyLineItem(QPen* pen, QBrush* brush);

  enum { Type = UserType + 2};
  int type() const {return Type;}

  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
  QPainterPath shape() const;

  PolyLine polyLine();
  void setPolyLine(const PolyLine& polyLine);

private:
  PolyLine m_polyLine;
  QPen* m_pen;
  QBrush* m_brush;
};

#endif // GRAPHICSPOLYLINEITEM_H
