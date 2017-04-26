// created on 2016-07-27

#ifndef ProductB1_h
#define ProductB1_h

#include "AbstractProductBI.h"

class ProductB1 : public AbstractProductBI
{
public:
  ProductB1();
  ~ProductB1();

  // interface AbstractProductBI
  std::string getDescription();
  void doSomething();
};

#endif // ProductB1_h
