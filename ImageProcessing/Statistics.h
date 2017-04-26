#ifndef STATISTICS_H
#define STATISTICS_H

#include <limits>

template<typename T>
class Statistics
{
public:
  Statistics();

  T minimum;
  T maximum;
  double meanValue;
};

template<typename T>
Statistics<T>::Statistics() :
  minimum(std::numeric_limits<T>::max()),
  maximum(std::numeric_limits<T>::min()),
  meanValue(0.0)
{

}

#endif // STATISTICS_H
