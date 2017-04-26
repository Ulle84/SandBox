#include "BurgerKingCheeseburger.h"
#include "BurgerKingFries.h"

#include "BurgerKing.h"

BurgerKing::BurgerKing()
{

}

BurgerKing::~BurgerKing()
{

}

CheeseburgerI* BurgerKing::createCheeseburger()
{
  return new BurgerKingCheeseburger();
}

FriesI* BurgerKing::createFries()
{
  return new BurgerKingFries();
}
