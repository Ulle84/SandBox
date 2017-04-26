#include "FlingMove.h"

#include <iostream>
#include <QString>

FlingMove::FlingMove()
{
}

FlingMove::FlingMove(Fling fling, Direction direction) :
  fling(fling), direction(direction)
{
}

void FlingMove::print()
{
  std::cout << "----------------------" << std::endl;
  std::cout << "flingMove" << std::endl;
  fling.print();
  QString directionString;

  switch (direction)
  {
  case UP:
    directionString = "up";
    break;

  case DOWN:
    directionString = "down";
    break;

  case LEFT:
    directionString = "left";
    break;

  case RIGHT:
    directionString = "right";
    break;

  case UNDEFINED:
    directionString = "undefined";
    break;

  default:
    directionString = "undefined";
  }

  std::cout << "direction: " << directionString.toStdString().c_str() << std::endl;
}
