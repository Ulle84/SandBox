// created on 2016-07-27

#ifndef ProductA2_h
#define ProductA2_h

#include "AbstractProductAI.h"

class ProductA2 : public AbstractProductAI
{
public:
  ProductA2();
  ~ProductA2();

  // interface AbstractProductA
  std::string getDescription();
};

#endif // ProductA2_h
