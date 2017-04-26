#ifndef EDGE_H
#define EDGE_H

#include <list>
#include "Point.h"

class Edge
{
public:
  Edge(const Point& position, float direction, float strength);

  Point getPosition();

private:
  Point m_position;
  float m_direction;
  float m_strength;
};

typedef std::list<Edge> Edges;

#endif // EDGE_H
