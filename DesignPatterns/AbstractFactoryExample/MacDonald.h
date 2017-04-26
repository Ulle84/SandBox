// created on 2016-07-29

#ifndef MacDonald_h
#define MacDonald_h

#include "BurgerShopI.h"

class MacDonald : public BurgerShopI
{
public:
  MacDonald();
  ~MacDonald();

  // interface BurgerShopI
  CheeseburgerI* createCheeseburger();
  FriesI* createFries();
};

#endif // MacDonald_h