// created on 2016-07-27

#ifndef ConcreteFactory2_h
#define ConcreteFactory2_h

#include "AbstractFactoryI.h"

class ConcreteFactory2 : public AbstractFactoryI
{
public:
  ConcreteFactory2();
  ~ConcreteFactory2();

  // interface AbstractFactoryI
  virtual AbstractProductAI* createProductA();
  virtual AbstractProductBI* createProductB();
};

#endif // ConcreteFactory2_h
