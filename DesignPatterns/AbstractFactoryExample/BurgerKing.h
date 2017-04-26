// created on 2016-07-29

#ifndef BurgerKing_h
#define BurgerKing_h

#include "BurgerShopI.h"

class BurgerKing : public BurgerShopI
{
public:
  BurgerKing();
  ~BurgerKing();

  // interface BurgerShopI
  CheeseburgerI* createCheeseburger();
  FriesI* createFries();
};

#endif // BurgerKing_h