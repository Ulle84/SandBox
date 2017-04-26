#include <QDebug>
#include <QPainter>

#include "Converter.h"
#include "RectangleRotated.h"

RectangleRotated::RectangleRotated(QPen* pen, QBrush* brush) :
  m_pen(pen),
  m_brush(brush)
{
}

RectangleRotated::~RectangleRotated()
{
}

QRectF RectangleRotated::boundingRect() const
{
  return Converter::toQRectF(m_rectangle.boundingRectangle());
}

void RectangleRotated::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setPen(*m_pen);
  painter->setBrush(*m_brush);

  painter->drawLine(Converter::toQPointF(m_rectangle.topLeft()), Converter::toQPointF(m_rectangle.bottomLeft()));
  painter->drawLine(Converter::toQPointF(m_rectangle.bottomLeft()), Converter::toQPointF(m_rectangle.bottomRight()));
  painter->drawLine(Converter::toQPointF(m_rectangle.bottomRight()), Converter::toQPointF(m_rectangle.topRight()));
  painter->drawLine(Converter::toQPointF(m_rectangle.topRight()), Converter::toQPointF(m_rectangle.topLeft()));
}

QPainterPath RectangleRotated::shape() const
{
  QPainterPath path;
  path.moveTo(Converter::toQPointF(m_rectangle.topLeft()));
  path.lineTo(Converter::toQPointF(m_rectangle.bottomLeft()));
  path.lineTo(Converter::toQPointF(m_rectangle.bottomRight()));
  path.lineTo(Converter::toQPointF(m_rectangle.topRight()));
  path.lineTo(Converter::toQPointF(m_rectangle.topLeft()));
  return path;
}

Rectangle RectangleRotated::rectangle()
{
  return m_rectangle;
}

void RectangleRotated::setRectangle(const Rectangle &rectangle)
{
  prepareGeometryChange();
  m_rectangle = rectangle;
}
