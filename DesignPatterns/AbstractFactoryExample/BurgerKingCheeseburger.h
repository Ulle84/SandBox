// created on 2016-07-29

#ifndef BurgerKingCheeseburger_h
#define BurgerKingCheeseburger_h

#include "CheeseburgerI.h"

class BurgerKingCheeseburger : public CheeseburgerI
{
public:
  BurgerKingCheeseburger();
  ~BurgerKingCheeseburger();

  // interface CheeseburgerI
  double getPrice();
};

#endif // BurgerKingCheeseburger_h