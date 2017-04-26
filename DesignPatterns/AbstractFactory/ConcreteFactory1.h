// created on 2016-07-27

#ifndef ConcreteFactory1_h
#define ConcreteFactory1_h

#include "AbstractFactoryI.h"

class ConcreteFactory1 : public AbstractFactoryI
{
public:
  ConcreteFactory1();
  ~ConcreteFactory1();

  // interface AbstractFactoryI
  virtual AbstractProductAI* createProductA();
  virtual AbstractProductBI* createProductB();
};

#endif // ConcreteFactory1_h
