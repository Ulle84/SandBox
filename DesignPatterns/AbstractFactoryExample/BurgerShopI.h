// created on 2016-07-29

#ifndef BurgerShopI_h
#define BurgerShopI_h

#include "CheeseburgerI.h"
#include "FriesI.h"

class BurgerShopI
{
public:
  virtual ~BurgerShopI(){}

  virtual CheeseburgerI* createCheeseburger() = 0;
  virtual FriesI* createFries() = 0;
};

#endif // BurgerShopI_h