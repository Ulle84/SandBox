// created on 2016-07-27

#ifndef ProductA1_h
#define ProductA1_h

#include "AbstractProductAI.h"

class ProductA1 : public AbstractProductAI
{
public:
  ProductA1();
  ~ProductA1();

  // interface AbstractProductAI
  std::string getDescription();
};

#endif // ProductA1_h
