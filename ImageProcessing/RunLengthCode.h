#ifndef RUNLENGTHCODE_H
#define RUNLENGTHCODE_H

#include <list>

#include "Point.h"

class RunLength
{
public:
  RunLength(const Point& point, unsigned int length) : m_startPoint(point), m_length(length) {}
  Point m_startPoint;
  unsigned int m_length;
};

typedef std::list<RunLength> RunLengthCode;

/*class RunLengthCode
{
public:
  RunLengthCode();
};*/

#endif // RUNLENGTHCODE_H
