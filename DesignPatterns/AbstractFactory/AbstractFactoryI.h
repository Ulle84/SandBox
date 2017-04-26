// created on 2016-07-27

#ifndef AbstractFactoryI_h
#define AbstractFactoryI_h

#include "AbstractProductAI.h"
#include "AbstractProductBI.h"

class AbstractFactoryI
{
public:
  virtual ~AbstractFactoryI(){}

  virtual AbstractProductAI* createProductA() = 0;
  virtual AbstractProductBI* createProductB() = 0;
};

#endif // AbstractFactoryI_h
