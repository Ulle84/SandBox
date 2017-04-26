#ifndef BASE_PRIVATE_H
#define BASE_PRIVATE_H

#include "Base.h"

class BasePrivate
{
public:
  // declare empty virtual destructor, since this will become a base class
  virtual ~BasePrivate() {}

  int value;
};

#endif // BASE_PRIVATE_H
