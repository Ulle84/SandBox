#ifndef TEACHABLERECTANGLE_H
#define TEACHABLERECTANGLE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPen>
#include <QPoint>
#include <QVector>

#include "Teachable.h"

class TeachableRectangle : public Teachable
{
public:
  TeachableRectangle(QGraphicsRectItem* rectItem, QGraphicsScene* scene, QPen* pen);

  // Interface Techable
  void setTeachingPointsVisible(bool visible);
  bool hasGraphicsItem(QGraphicsItem* item);
  void positionChanged(QGraphicsEllipseItem* item, const QPointF& position);
  bool hasTeachingPoint(QGraphicsEllipseItem* item);
  QGraphicsEllipseItem* defaultTeachingPoint();

private:
  QPointF middle(const QPointF& start, const QPointF& end);

  QGraphicsRectItem* m_rectItem;
  QGraphicsScene* m_scene;
  QPen* m_pen;

  QGraphicsEllipseItem* m_topLeft;
  QGraphicsEllipseItem* m_top;
  QGraphicsEllipseItem* m_topRight;

  QGraphicsEllipseItem* m_left;
  QGraphicsEllipseItem* m_center;
  QGraphicsEllipseItem* m_right;

  QGraphicsEllipseItem* m_bottomLeft;
  QGraphicsEllipseItem* m_bottom;
  QGraphicsEllipseItem* m_bottomRight;
};

#endif // TEACHABLERECTANGLE_H
