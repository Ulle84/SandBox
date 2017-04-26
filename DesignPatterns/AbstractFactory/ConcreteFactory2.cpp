#include "ConcreteFactory2.h"
#include "ProductA2.h"
#include "ProductB2.h"

ConcreteFactory2::ConcreteFactory2()
{

}

ConcreteFactory2::~ConcreteFactory2()
{

}

AbstractProductAI* ConcreteFactory2::createProductA()
{
  return new ProductA2();
}

AbstractProductBI* ConcreteFactory2::createProductB()
{
  return new ProductB2();
}
