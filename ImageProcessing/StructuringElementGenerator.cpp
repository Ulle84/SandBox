#include "StructuringElementGenerator.h"
#include "PolyLine.h"

StructuringElementGenerator::StructuringElementGenerator()
{
}

StructuringElement StructuringElementGenerator::neighborhood4()
{
  StructuringElement structuringElement(3, 3);

  structuringElement.setValue(false, 0, 0);
  structuringElement.setValue(false, 2, 0);
  structuringElement.setValue(false, 0, 2);
  structuringElement.setValue(false, 2, 2);

  return structuringElement;
}

StructuringElement StructuringElementGenerator::neighborhood8()
{
  StructuringElement structuringElement(3, 3);
  return structuringElement;
}

StructuringElement StructuringElementGenerator::circle(unsigned int radius)
{
  unsigned int size = radius * 2 + 1;
  StructuringElement structuringElement(size, size);
  structuringElement.setAllValues(false);
  structuringElement.setCircle(true, Circle(structuringElement.getReferencePoint(), radius));

  return structuringElement;
}

StructuringElement StructuringElementGenerator::polyLineFillTest(unsigned int type, bool fill)
{
  unsigned int width = 15;
  unsigned int height = 15;
  PolyLine polyLine;

  switch(type)
  {
  case 0:
    width = 7;
    height = 7;
    polyLine.push_back(Point(1, 1));
    polyLine.push_back(Point(5, 1));
    polyLine.push_back(Point(5, 5));
    polyLine.push_back(Point(1, 1));
    break;

  case 1:
    width = 7;
    height = 3;
    polyLine.push_back(Point(1, 1));
    polyLine.push_back(Point(5, 1));
    break;

  case 2:
    width = 3;
    height = 7;
    polyLine.push_back(Point(1, 1));
    polyLine.push_back(Point(1, 5));
    break;

  case 3:
    width = 7;
    height = 7;
    polyLine.push_back(Point(1, 1));
    polyLine.push_back(Point(1, 5));
    polyLine.push_back(Point(5, 5));
    polyLine.push_back(Point(5, 1));
    polyLine.push_back(Point(1, 1));
    break;

  case 4:
    width = 9;
    height = 9;
    polyLine.push_back(Point(1, 1));
    polyLine.push_back(Point(4, 4));
    polyLine.push_back(Point(7, 1));
    polyLine.push_back(Point(7, 7));
    polyLine.push_back(Point(1, 7));
    polyLine.push_back(Point(1, 1));
    break;

  case 5:
    width = 9;
    height = 9;
    polyLine.push_back(Point(1, 2));
    polyLine.push_back(Point(3, 4));
    polyLine.push_back(Point(5, 1));
    polyLine.push_back(Point(7, 7));
    polyLine.push_back(Point(1, 7));
    polyLine.push_back(Point(1, 2));
    break;

  case 6:
    width = 7;
    height = 7;
    polyLine.push_back(Point(1, 3));
    polyLine.push_back(Point(3, 3));
    polyLine.push_back(Point(5, 1));
    polyLine.push_back(Point(5, 5));
    polyLine.push_back(Point(1, 5));
    polyLine.push_back(Point(1, 3));

  case 7:
    width = 7;
    height = 7;
    polyLine.push_back(Point(1, 3));
    polyLine.push_back(Point(2, 3));
    polyLine.push_back(Point(5, 1));
    polyLine.push_back(Point(5, 5));
    polyLine.push_back(Point(1, 5));
    polyLine.push_back(Point(1, 3));

    break;

  case 8:
    width = 9;
    height = 7;
    polyLine.push_back(Point(1, 1));
    polyLine.push_back(Point(4, 4));
    polyLine.push_back(Point(7, 1));
    polyLine.push_back(Point(7, 5));
    polyLine.push_back(Point(1, 5));
    polyLine.push_back(Point(1, 1));

    break;
  }

  polyLine.toRunLengthCode();

  StructuringElement structuringElement(width, height, false);
  structuringElement.setPolyLine(true, polyLine);

  if (fill)
  {
    structuringElement.fillBackground(false, true);
    structuringElement.invert();
    structuringElement.setPolyLine(true, polyLine);
  }

  return structuringElement;
}
