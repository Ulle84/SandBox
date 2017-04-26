#include <QDebug>
#include <QRectF>
#include <QPointF>

#include "Converter.h"
#include "TeachableRectangleRotated.h"
#include "MathHelper.h"
#include "Point.h"
#include "Line.h"


TeachableRectangleRotated::TeachableRectangleRotated(RectangleRotated *rectangleRotated, QGraphicsScene *scene, QPen *pen) :
  m_rectangleRotated(rectangleRotated),
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

  m_angle = scene->addEllipse(QRectF(), *m_pen);

  setTeachingPointsVisible(false);
}

void TeachableRectangleRotated::setTeachingPointsVisible(bool visible)
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

  m_angle->setVisible(visible);

  if (visible)
  {
    Rectangle rectangle = m_rectangleRotated->rectangle();

    QPointF topLeft = Converter::toQPointF(rectangle.topLeft());
    QPointF topRight = Converter::toQPointF(rectangle.topRight());
    QPointF bottomLeft = Converter::toQPointF(rectangle.bottomLeft());
    QPointF bottomRight = Converter::toQPointF(rectangle.bottomRight());

    float radius = 5.0;

    float factor = 5.0;

    if (rectangle.width() < factor * radius)
    {
      radius = rectangle.width() / factor;
    }

    if (rectangle.height() < factor * radius)
    {
      radius = rectangle.height() / factor;
    }

    m_topLeft->setRect(Converter::toQRectF(topLeft, radius));
    m_top->setRect(Converter::toQRectF(middle(topLeft, topRight), radius));
    m_topRight->setRect(Converter::toQRectF(topRight, radius));

    m_left->setRect(Converter::toQRectF(middle(topLeft, bottomLeft), radius));
    m_center->setRect(Converter::toQRectF(middle(topLeft, bottomRight), radius));
    m_right->setRect(Converter::toQRectF(middle(topRight, bottomRight), radius));

    m_bottomLeft->setRect(Converter::toQRectF(bottomLeft, radius));
    m_bottom->setRect(Converter::toQRectF(middle(bottomLeft, bottomRight), radius));
    m_bottomRight->setRect(Converter::toQRectF(bottomRight, radius));

    QPointF teachAngle = Converter::toQPointF(MathHelper::calcEndPoint(rectangle.topRight(), rectangle.angle(), radius * 2.5));
    m_angle->setRect(Converter::toQRectF(teachAngle, radius));
  }
}

bool TeachableRectangleRotated::hasGraphicsItem(QGraphicsItem *item)
{
  return m_rectangleRotated == item;
}

void TeachableRectangleRotated::positionChanged(QGraphicsEllipseItem *item, const QPointF &position)
{
  Rectangle rect = m_rectangleRotated->rectangle();

  if (item == m_topLeft)
  {
    rect.setTopLeft(Converter::toPoint(position));
  }
  else if (item == m_top)
  {
    float width = rect.width();
    rect.setTopRight(Converter::toPoint(position));
    rect.setWidth(width);
  }
  else if (item == m_topRight)
  {
    rect.setTopRight(Converter::toPoint(position));
  }
  else if (item == m_left)
  {
    float height = rect.height();
    rect.setBottomLeft(Converter::toPoint(position));
    rect.setHeight(height);
  }
  else if (item == m_center)
  {
    rect.moveCenter(Converter::toPoint(position));
  }
  else if (item == m_right)
  {
    float height = rect.height();
    rect.setBottomRight(Converter::toPoint(position));
    rect.setHeight(height);
  }
  else if (item == m_bottomLeft)
  {
    rect.setBottomLeft(Converter::toPoint(position));
  }
  else if (item == m_bottom)
  {
    float width = rect.width();
    rect.setBottomRight(Converter::toPoint(position));
    rect.setWidth(width);
  }
  else if (item == m_bottomRight)
  {
    rect.setBottomRight(Converter::toPoint(position));
  }
  else if (item == m_angle)
  {
    Line line(rect.topLeft(), Converter::toPoint(position));
    rect.setAngle(line.angle());
  }

  m_rectangleRotated->setRectangle(rect);
}

bool TeachableRectangleRotated::hasTeachingPoint(QGraphicsEllipseItem *item)
{
  bool teachingPointFound = false;

  teachingPointFound |= (m_topLeft == item || m_top == item || m_topRight == item);
  teachingPointFound |= (m_left == item || m_center == item || m_right == item);
  teachingPointFound |= (m_bottomLeft == item || m_bottom == item || m_bottomRight == item);
  teachingPointFound |= (m_angle == item);

  return teachingPointFound;
}

QGraphicsEllipseItem *TeachableRectangleRotated::defaultTeachingPoint()
{
  return m_bottomRight;
}

QPointF TeachableRectangleRotated::middle(const QPointF &start, const QPointF &end)
{
  qreal x = start.x() + (end.x() - start.x()) / 2;
  qreal y = start.y() + (end.y() - start.y()) / 2;

  return QPointF(x, y);
}
