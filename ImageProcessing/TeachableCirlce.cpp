#include <QDebug>
#include <qmath.h>

#include <QLineF>

#include "Converter.h"

#include "TeachableCirlce.h"

TeachableCirlce::TeachableCirlce(QGraphicsEllipseItem *ellipseItem, QGraphicsScene *scene, QPen *pen) :
  m_ellipseItem(ellipseItem),
  m_scene(scene),
  m_pen(pen)
{
  m_center = scene->addEllipse(QRectF(), *m_pen);
  m_pointOnCircle = scene->addEllipse(QRectF(), *m_pen);
  setTeachingPointsVisible(false);
}

void TeachableCirlce::setTeachingPointsVisible(bool visible)
{
  m_center->setVisible(visible);
  m_pointOnCircle->setVisible(visible);

  if (visible)
  {
    float radius = 5.0;
    float factor = 2.5;

    QLineF line(m_ellipseItem->rect().center(), m_teachedPointOnCircle);

    if (line.length() < factor * radius)
    {
      radius = line.length() / factor;
    }

    m_center->setRect(Converter::toQRectF(m_ellipseItem->rect().center(), radius));
    m_pointOnCircle->setRect(Converter::toQRectF(m_teachedPointOnCircle, radius));
  }
}

bool TeachableCirlce::hasGraphicsItem(QGraphicsItem *item)
{
  return m_ellipseItem == item;
}

void TeachableCirlce::positionChanged(QGraphicsEllipseItem *item, const QPointF &position)
{
  QRectF rect = m_ellipseItem->rect();

  if (item == m_center)
  {
    QPointF delta = position - rect.center();
    m_teachedPointOnCircle += delta;

    rect.moveCenter(position);
  }
  else if (item == m_pointOnCircle)
  {
    m_teachedPointOnCircle = position;

    QPointF center = rect.center();

    QPointF delta = position - center;

    double r = sqrt(delta.x() * delta.x() + delta.y() * delta.y());

    QPointF p1(center.x() - r, center.y() - r);
    QPointF p2(center.x() + r, center.y() + r);
    rect = QRectF(p1, p2);
  }

  m_ellipseItem->setRect(rect);
}

bool TeachableCirlce::hasTeachingPoint(QGraphicsEllipseItem *item)
{
  return item == m_center || item == m_pointOnCircle;
}

QGraphicsEllipseItem *TeachableCirlce::defaultTeachingPoint()
{
  return m_pointOnCircle;
}
