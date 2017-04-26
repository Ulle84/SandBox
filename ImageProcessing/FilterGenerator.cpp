#include "FilterGenerator.h"

FilterGenerator::FilterGenerator()
{
}

Filter FilterGenerator::mean(unsigned int width, unsigned int height)
{
  if (height == 0)
  {
    height = width;
  }

  Filter filter(width, height);

  filter.setAllValues(1);
  filter.setPreFactor(1.0 / (width * height));

  return filter;
}

Filter FilterGenerator::binomial(unsigned int width, unsigned int height)
{
  if (height == 0)
  {
    height = width;
  }

  if (width % 2 == 0)
  {
    width++;
  }

  if (height % 2 == 0)
  {
    height++;
  }

  Filter filter(width, height);
  filter.setBinomialValues();
  filter.setPreFactor(1.0 / filter.getSumOfAllValues());

  return filter;
}

Filter FilterGenerator::laplacian()
{
  Filter filter(3, 3);

  filter.setValue(-1, 1, 0);
  filter.setValue(-1, 0, 1);
  filter.setValue( 4, 1, 1);
  filter.setValue(-1, 2, 1);
  filter.setValue(-1, 1, 2);

  return filter;
}

Filter FilterGenerator::laplacianBig()
{
  Filter filter(9, 9);

  filter.setValue(  0, 0, 0);  filter.setValue(  1, 1, 0); filter.setValue(  1, 2, 0); filter.setValue(  2, 3, 0); filter.setValue(  2, 4, 0); filter.setValue(  2, 5, 0); filter.setValue(  1, 6, 0); filter.setValue(  1, 7, 0); filter.setValue(  0, 8, 0);
  filter.setValue(  1, 0, 1);  filter.setValue(  2, 1, 1); filter.setValue(  4, 2, 1); filter.setValue(  5, 3, 1); filter.setValue(  5, 4, 1); filter.setValue(  5, 5, 1); filter.setValue(  4, 6, 1); filter.setValue(  2, 7, 1); filter.setValue(  1, 8, 1);
  filter.setValue(  1, 0, 2);  filter.setValue(  4, 1, 2); filter.setValue(  5, 2, 2); filter.setValue(  3, 3, 2); filter.setValue(  0, 4, 2); filter.setValue(  3, 5, 2); filter.setValue(  5, 6, 2); filter.setValue(  4, 7, 2); filter.setValue(  1, 8, 2);
  filter.setValue(  2, 0, 3);  filter.setValue(  5, 1, 3); filter.setValue(  3, 2, 3); filter.setValue(-12, 3, 3); filter.setValue(-24, 4, 3); filter.setValue(-12, 5, 3); filter.setValue(  3, 6, 3); filter.setValue(  5, 7, 3); filter.setValue(  2, 8, 3);
  filter.setValue(  2, 0, 4);  filter.setValue(  5, 1, 4); filter.setValue(  0, 2, 4); filter.setValue(-24, 3, 4); filter.setValue(-40, 4, 4); filter.setValue(-24, 5, 4); filter.setValue(  0, 6, 4); filter.setValue(  5, 7, 4); filter.setValue(  2, 8, 4);
  filter.setValue(  2, 0, 5);  filter.setValue(  5, 1, 5); filter.setValue(  3, 2, 5); filter.setValue(-12, 3, 5); filter.setValue(-24, 4, 5); filter.setValue(-12, 5, 5); filter.setValue(  3, 6, 5); filter.setValue(  5, 7, 5); filter.setValue(  2, 8, 5);
  filter.setValue(  1, 0, 6);  filter.setValue(  4, 1, 6); filter.setValue(  5, 2, 6); filter.setValue(  3, 3, 6); filter.setValue(  0, 4, 6); filter.setValue(  3, 5, 6); filter.setValue(  5, 6, 6); filter.setValue(  4, 7, 6); filter.setValue(  1, 8, 6);
  filter.setValue(  1, 0, 7);  filter.setValue(  2, 1, 7); filter.setValue(  4, 2, 7); filter.setValue(  5, 3, 7); filter.setValue(  5, 4, 7); filter.setValue(  5, 5, 7); filter.setValue(  4, 6, 7); filter.setValue(  2, 7, 7); filter.setValue(  1, 8, 7);
  filter.setValue(  0, 0, 8);  filter.setValue(  1, 1, 8); filter.setValue(  1, 2, 8); filter.setValue(  2, 3, 8); filter.setValue(  2, 4, 8); filter.setValue(  2, 5, 8); filter.setValue(  1, 6, 8); filter.setValue(  1, 7, 8); filter.setValue(  0, 8, 8);

  return filter;
}

Filter FilterGenerator::laplacian2()
{
  Filter filter(3, 3);
  filter.setAllValues(-1);
  filter.setValue(8, 1, 1);

  filter.printValuesToConsole("laplacian2");

  return filter;
}

Filter FilterGenerator::sobelVertical()
{
  Filter filter (3, 3);
  filter.setValue(-1, 0, 0); filter.setValue(1, 2, 0);
  filter.setValue(-2, 0, 1); filter.setValue(2, 2, 1);
  filter.setValue(-1, 0, 2); filter.setValue(1, 2, 2);

  filter.setInvertNegativeResultValues(true);

  return filter;
}

Filter FilterGenerator::sobelHorizontal()
{
  Filter filter = sobelVertical();
  filter.rotateBy90DegreeClockwise();
  return filter;
}
