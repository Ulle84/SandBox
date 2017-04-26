#include <QPainter>

#include "GraphicsPolyLineItem.h"
#include "Converter.h"

GraphicsPolyLineItem::GraphicsPolyLineItem(QPen *pen, QBrush *brush) :
  m_pen(pen),
  m_brush(brush)
{
}

QRectF GraphicsPolyLineItem::boundingRect() const
{
  return Converter::toQRectF(m_polyLine.boundingRectangle());
}

void GraphicsPolyLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setPen(*m_pen);
  painter->setBrush(*m_brush);

  if (m_polyLine.size() < 2)
  {
    return;
  }

  auto itPrevious = m_polyLine.begin();
  for (auto it = m_polyLine.begin(); it != m_polyLine.end(); it++)
  {
    if (it == m_polyLine.begin())
    {
      continue;
    }

    painter->drawLine(Converter::toQPointF(*itPrevious), Converter::toQPointF(*it));

    itPrevious = it;
  }
}

QPainterPath GraphicsPolyLineItem::shape() const
{
  return QPainterPath(); // TODO
}

PolyLine GraphicsPolyLineItem::polyLine()
{
  return m_polyLine;
}

void GraphicsPolyLineItem::setPolyLine(const PolyLine &polyLine)
{
  prepareGeometryChange();
  m_polyLine = polyLine;
}
