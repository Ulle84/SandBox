#include <QDebug>

#include "TeachablePolyLine.h"
#include "Converter.h"
#include "Line.h"
#include "MathHelper.h"

TeachablePolyLine::TeachablePolyLine(GraphicsPolyLineItem *polyLineItem, QGraphicsScene *scene, QPen *pen) :
  m_polyLineItem(polyLineItem),
  m_scene(scene),
  m_pen(pen)
{
  m_prepend = m_scene->addEllipse(QRectF(), *m_pen);
  m_append = m_scene->addEllipse(QRectF(), *m_pen);

  PolyLine polyLine = m_polyLineItem->polyLine();

  for (auto it = polyLine.begin(); it != polyLine.end(); it++)
  {
    m_edgePoints.append(m_scene->addEllipse(QRectF(), *m_pen));
  }  

  setTeachingPointsVisible(false);
}

void TeachablePolyLine::setTeachingPointsVisible(bool visible)
{
  PolyLine polyLine = m_polyLineItem->polyLine();

  m_prepend->setVisible(polyLine.isClosed() ? false : visible);
  m_append->setVisible(polyLine.isClosed() ? false : visible);

  for (auto it = m_edgePoints.begin(); it != m_edgePoints.end(); it++)
  {
    (*it)->setVisible(visible);
  }


  if (visible)
  {
    float radius = 5.0;

    /*m_center = center();

    QLineF line = m_lineItem->line();


    float factor = 5.0;

    if (line.length() < factor * radius)
    {
      radius = line.length() / factor;
    }*/



    if (!polyLine.isClosed())
    {
      auto it1 = polyLine.begin();
      auto it2 = it1++;
      Line line1 = Line(*it1, *it2);

      auto it3 = polyLine.rbegin();
      auto it4 = it3++;
      Line line2 = Line(*it3, *it4);

      Point prepend = MathHelper::calcEndPoint(polyLine.front(), line1.angle(), radius * 2.5);
      Point append = MathHelper::calcEndPoint(polyLine.back(), line2.angle(), radius * 2.5);
      Point close = MathHelper::calcEndPoint(polyLine.back(), line2.angle(), radius * 5);

      m_prepend->setRect(Converter::toQRectF(prepend, radius));
      m_append->setRect(Converter::toQRectF(append, radius));
    }

    unsigned int counter = 0;
    for (auto it = polyLine.begin(); it != polyLine.end(); it++)
    {
      if (counter < m_edgePoints.size())
      {
        m_edgePoints[counter]->setRect(Converter::toQRectF(*it, radius));
      }
      counter++;
    }
  }
}

bool TeachablePolyLine::hasGraphicsItem(QGraphicsItem *item)
{
  return m_polyLineItem == item;
}

void TeachablePolyLine::positionChanged(QGraphicsEllipseItem *item, const QPointF &position)
{
  PolyLine polyLine = m_polyLineItem->polyLine();

  if (isEdgePoint(item))
  {
    auto itPolyLineLast = polyLine.end();
    itPolyLineLast--;

    auto itLastEdgePoint = m_edgePoints.end();
    itLastEdgePoint--;

    auto itPolyLine = polyLine.begin();

    for (auto it = m_edgePoints.begin(); it != m_edgePoints.end(); it++)
    {
      if (*it == item)
      {
        itPolyLine->setX(position.x());
        itPolyLine->setY(position.y());

        // snipping to start or end point
        if ((itPolyLine == itPolyLineLast || itPolyLine == polyLine.begin()) && polyLine.size() > 3 && !polyLine.isClosed())
        {
          QPointF snapPoint = Converter::toQPointF(itPolyLine == itPolyLineLast ? polyLine.front() : polyLine.back());
          QPointF delta = position - snapPoint;

          float sd = 10.0; // snipping distance
          if (MathHelper::isBetween(-sd, delta.x(), sd) && MathHelper::isBetween(-sd, delta.y(), sd))
          {
            if (itPolyLine == itPolyLineLast)
            {
              itPolyLine->setX(polyLine.front().x());
              itPolyLine->setY(polyLine.front().y());
            }
            else
            {
              itPolyLine->setX(polyLine.back().x());
              itPolyLine->setY(polyLine.back().y());
            }
          }
        }

        /*if (polyLine.isClosed() && (it == m_edgePoints.begin() || it == itLastEdgePoint))
        {
          if (it == itLastEdgePoint)
          {
            polyLine.begin()->setX(position.x());
            polyLine.begin()->setY(position.y());
          }
          else
          {
            polyLine.rbegin()->setX(position.x());
            polyLine.rbegin()->setY(position.y());
          }
        }*/

        break;
      }

      itPolyLine++;

      if (itPolyLine == polyLine.end())
      {
        break;
      }
    }
  }
  else if (item == m_append)
  {
    polyLine.push_back(Converter::toPoint(position));
    m_edgePoints.append(m_append);
    m_append = m_scene->addEllipse(QRectF(), *m_pen);
  }
  else if (item == m_prepend)
  {
    polyLine.push_front(Converter::toPoint(position));
    m_edgePoints.prepend(m_prepend);
    m_prepend = m_scene->addEllipse(QRectF(), *m_pen);
  }

  m_polyLineItem->setPolyLine(polyLine);
}

bool TeachablePolyLine::hasTeachingPoint(QGraphicsEllipseItem *item)
{
  return item == m_append || item == m_prepend || isEdgePoint(item);
}

QGraphicsEllipseItem *TeachablePolyLine::defaultTeachingPoint()
{
  return m_edgePoints.last();
}

bool TeachablePolyLine::isEdgePoint(QGraphicsEllipseItem *item)
{
  for (auto it = m_edgePoints.begin(); it != m_edgePoints.end(); it++)
  {
    if (*it == item)
    {
      return true;
    }
  }
  return false;
}

QPointF TeachablePolyLine::center()
{
  QPointF center;

  PolyLine polyLine = m_polyLineItem->polyLine();

  if (polyLine.size() == 2)
  {
    QPointF start = Converter::toQPointF(polyLine.front());
    QPointF end = Converter::toQPointF(polyLine.back());

    center.setX(start.x() + (end.x() - start.x()) / 2);
    center.setY(start.y() + (end.y() - start.y()) / 2);
  }

  return center;
}
