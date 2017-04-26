#ifndef FLINGMOVE_H
#define FLINGMOVE_H

#include "Fling.h"

enum Direction {UNDEFINED, UP, RIGHT, DOWN, LEFT};

class FlingMove
{
public:
  FlingMove();
  FlingMove(Fling fling, Direction direction);
  Direction direction;
  Fling fling;
  void print();
};

#endif // FLINGMOVE_H
