#include "MacDonaldCheeseburger.h"
#include "MacDonaldFries.h"

#include "MacDonald.h"

MacDonald::MacDonald()
{

}

MacDonald::~MacDonald()
{

}

CheeseburgerI* MacDonald::createCheeseburger()
{
  return new MacDonaldCheeseburger();
}

FriesI* MacDonald::createFries()
{
  return new MacDonaldFries();
}
