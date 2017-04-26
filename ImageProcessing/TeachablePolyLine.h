#ifndef TEACHABLEPOLYLINE_H
#define TEACHABLEPOLYLINE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QPen>
#include <QPoint>
#include <QVector>

#include "Teachable.h"
#include "GraphicsPolyLineItem.h"

class TeachablePolyLine : public Teachable
{
public:
  TeachablePolyLine(GraphicsPolyLineItem* polyLineItem, QGraphicsScene* scene, QPen* pen);

  // Interface Techable
  void setTeachingPointsVisible(bool visible);
  bool hasGraphicsItem(QGraphicsItem* item);
  void positionChanged(QGraphicsEllipseItem* item, const QPointF& position);
  bool hasTeachingPoint(QGraphicsEllipseItem* item);
  QGraphicsEllipseItem* defaultTeachingPoint();

private:
  bool isEdgePoint(QGraphicsEllipseItem* item);

  QPointF center(); // TODO use this function and define QGraphicsEllipseItem* m_center

  GraphicsPolyLineItem* m_polyLineItem;
  QGraphicsScene* m_scene;
  QPen* m_pen;

  QVector<QGraphicsEllipseItem*> m_edgePoints;

  QGraphicsEllipseItem* m_append;
  QGraphicsEllipseItem* m_prepend;
};

#endif // TEACHABLEPOLYLINE_H
