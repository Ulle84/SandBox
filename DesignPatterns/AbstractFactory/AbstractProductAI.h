// created on 2016-07-27

#ifndef AbstractProductAI_h
#define AbstractProductAI_h

#include <string>

class AbstractProductAI
{
public:
  virtual ~AbstractProductAI(){}

  virtual std::string getDescription() = 0;
};

#endif // AbstractProductAI_h
