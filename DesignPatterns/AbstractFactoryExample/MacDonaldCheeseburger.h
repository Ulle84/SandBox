// created on 2016-07-29

#ifndef MacDonaldCheeseburger_h
#define MacDonaldCheeseburger_h

#include "CheeseburgerI.h"

class MacDonaldCheeseburger : public CheeseburgerI
{
public:
  MacDonaldCheeseburger();
  ~MacDonaldCheeseburger();

  // interface CheeseburgerI
  double getPrice();
};

#endif // MacDonaldCheeseburger_h