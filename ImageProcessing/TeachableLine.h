#ifndef TEACHABLELINE_H
#define TEACHABLELINE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPen>
#include <QPoint>

#include "Teachable.h"

class TeachableLine : public Teachable
{
public:
  TeachableLine(QGraphicsLineItem* lineItem, QGraphicsScene* scene, QPen* pen);

  // Interface Techable
  void setTeachingPointsVisible(bool visible);
  bool hasGraphicsItem(QGraphicsItem* item);
  void positionChanged(QGraphicsEllipseItem* item, const QPointF& position);
  bool hasTeachingPoint(QGraphicsEllipseItem* item);
  QGraphicsEllipseItem* defaultTeachingPoint();

private:
  QPointF center();

  QGraphicsLineItem* m_lineItem;
  QGraphicsScene* m_scene;
  QPen* m_pen;

  QGraphicsEllipseItem* m_startPoint;
  QGraphicsEllipseItem* m_centerPoint;
  QGraphicsEllipseItem* m_endPoint;

  QPointF m_center;
};

#endif // TEACHABLELINE_H
