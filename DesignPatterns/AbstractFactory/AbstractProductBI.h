// created on 2016-07-27

#ifndef AbstractProductBI_h
#define AbstractProductBI_h

#include <string>

class AbstractProductBI
{
public:
  virtual ~AbstractProductBI(){}

  virtual std::string getDescription() = 0;
  virtual void doSomething() = 0;
};

#endif // AbstractProductBI_h
