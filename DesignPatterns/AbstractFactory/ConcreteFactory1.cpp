#include "ConcreteFactory1.h"

#include "ProductA1.h"
#include "ProductB1.h"

ConcreteFactory1::ConcreteFactory1()
{

}

ConcreteFactory1::~ConcreteFactory1()
{

}

AbstractProductAI* ConcreteFactory1::createProductA()
{
  return new ProductA1();
}

AbstractProductBI* ConcreteFactory1::createProductB()
{
  return new ProductB1();
}
