#ifndef FILTERGENERATOR_H
#define FILTERGENERATOR_H

#include "Matrix.h"

class FilterGenerator
{
public:
  FilterGenerator();

  static Filter mean(unsigned int width, unsigned int height = 0);
  static Filter binomial(unsigned int width, unsigned int height = 0);
  static Filter laplacian();
  static Filter laplacianBig();
  static Filter laplacian2();
  static Filter sobelHorizontal();
  static Filter sobelVertical();
};

#endif // FILTERGENERATOR_H
