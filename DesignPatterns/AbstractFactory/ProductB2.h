// created on 2016-07-27

#ifndef ProductB2_h
#define ProductB2_h

#include "AbstractProductBI.h"

class ProductB2 : public AbstractProductBI
{
public:
  ProductB2();
  ~ProductB2();

  // interface AbstractProductBI
  std::string getDescription();
  void doSomething();
};

#endif // ProductB2_h
