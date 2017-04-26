// created on 2016-07-29

#ifndef BurgerKingFries_h
#define BurgerKingFries_h

#include "FriesI.h"

class BurgerKingFries : public FriesI
{
public:
  BurgerKingFries();
  ~BurgerKingFries();

  // interface FriesI
  double getPrice();
};

#endif // BurgerKingFries_h