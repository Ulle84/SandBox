#ifndef TEACHABLE_H
#define TEACHABLE_H

class QPointF;
class QGraphicsItem;
class QGraphicsEllipseItem;

class Teachable
{
public:
  virtual ~Teachable(){}

  virtual void setTeachingPointsVisible(bool visible) = 0;
  virtual bool hasGraphicsItem(QGraphicsItem* item) = 0;
  virtual void positionChanged(QGraphicsEllipseItem* item, const QPointF& position) = 0;
  virtual bool hasTeachingPoint(QGraphicsEllipseItem* item) = 0;
  virtual QGraphicsEllipseItem* defaultTeachingPoint() = 0;
};

#endif // TEACHABLE_H
