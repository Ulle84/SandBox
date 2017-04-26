#include <QDebug>

#include "Converter.h"

#include "TeachableRectangle.h"


TeachableRectangle::TeachableRectangle(QGraphicsRectItem *rectItem, QGraphicsScene *scene, QPen *pen) :
  m_rectItem(rectItem),
  m_scene(scene),
  m_pen(pen)
{
  m_topLeft = scene->addEllipse(QRectF(), *m_pen);
  m_top = scene->addEllipse(QRectF(), *m_pen);
  m_topRight = scene->addEllipse(QRectF(), *m_pen);

  m_left = scene->addEllipse(QRectF(), *m_pen);
  m_center = scene->addEllipse(QRectF(), *m_pen);
  m_right = scene->addEllipse(QRectF(), *m_pen);

  m_bottomLeft = scene->addEllipse(QRectF(), *m_pen);
  m_bottom = scene->addEllipse(QRectF(), *m_pen);
  m_bottomRight = scene->addEllipse(QRectF(), *m_pen);

  setTeachingPointsVisible(false);
}

void TeachableRectangle::setTeachingPointsVisible(bool visible)
{
  m_topLeft->setVisible(visible);
  m_top->setVisible(visible);
  m_topRight->setVisible(visible);

  m_left->setVisible(visible);
  m_center->setVisible(visible);
  m_right->setVisible(visible);

  m_bottomLeft->setVisible(visible);
  m_bottom->setVisible(visible);
  m_bottomRight->setVisible(visible);

  if (visible)
  {
    QRectF rect = m_rectItem->rect();

    QPointF topLeft = rect.topLeft();
    QPointF topRight = rect.topRight();
    QPointF bottomLeft = rect.bottomLeft();
    QPointF bottomRight = rect.bottomRight();

    qreal width = rect.width() < 0 ? -rect.width() : rect.width();
    qreal heightx = rect.height() < 0 ? -rect.height() : rect.height();

    float radius = 5.0;

    float factor = 5.0;

    if (width < factor * radius)
    {
      radius = rect.width() / factor;
    }

    if (rect.height() < factor * radius)
    {
      radius = rect.height() / factor;
    }

    m_topLeft->setRect(Converter::toQRectF(topLeft, radius));
    m_top->setRect(Converter::toQRectF(middle(topLeft, topRight), radius));
    m_topRight->setRect(Converter::toQRectF(topRight, radius));

    m_left->setRect(Converter::toQRectF(middle(topLeft, bottomLeft), radius));
    m_center->setRect(Converter::toQRectF(rect.center(), radius));
    m_right->setRect(Converter::toQRectF(middle(topRight, bottomRight), radius));

    m_bottomLeft->setRect(Converter::toQRectF(bottomLeft, radius));
    m_bottom->setRect(Converter::toQRectF(middle(bottomLeft, bottomRight), radius));
    m_bottomRight->setRect(Converter::toQRectF(bottomRight, radius));
  }
}

bool TeachableRectangle::hasGraphicsItem(QGraphicsItem *item)
{
  return m_rectItem == item;
}

void TeachableRectangle::positionChanged(QGraphicsEllipseItem *item, const QPointF &position)
{
  QRectF rect = m_rectItem->rect();

  if (item == m_topLeft)
  {
    rect.setTopLeft(position);
  }
  else if (item == m_top)
  {
    rect.setTop(position.y());
  }
  else if (item == m_topRight)
  {
    rect.setTopRight(position);
  }
  else if (item == m_left)
  {
    rect.setLeft(position.x());
  }
  else if (item == m_center)
  {
    rect.moveCenter(position);
  }
  else if (item == m_right)
  {
    rect.setRight(position.x());
  }
  else if (item == m_bottomLeft)
  {
    rect.setBottomLeft(position);
  }
  else if (item == m_bottom)
  {
    rect.setBottom(position.y());
  }
  else if (item == m_bottomRight)
  {
    rect.setBottomRight(position);
  }


  m_rectItem->setRect(rect);
}

QPointF TeachableRectangle::middle(const QPointF &start, const QPointF &end)
{
  qreal x = start.x() + (end.x() - start.x()) / 2;
  qreal y = start.y() + (end.y() - start.y()) / 2;

  return QPointF(x, y);
}

bool TeachableRectangle::hasTeachingPoint(QGraphicsEllipseItem *item)
{
  bool teachingPointFound = false;

  teachingPointFound |= (m_topLeft == item || m_top == item || m_topRight == item);
  teachingPointFound |= (m_left == item || m_center == item || m_right == item);
  teachingPointFound |= (m_bottomLeft == item || m_bottom == item || m_bottomRight == item);

  return teachingPointFound;
}

QGraphicsEllipseItem *TeachableRectangle::defaultTeachingPoint()
{
  return m_bottomRight;
}
