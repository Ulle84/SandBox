// created on 2016-07-29

#ifndef MacDonaldFries_h
#define MacDonaldFries_h

#include "FriesI.h"

class MacDonaldFries : public FriesI
{
public:
  MacDonaldFries();
  ~MacDonaldFries();

  // interface FriesI
  double getPrice();
};

#endif // MacDonaldFries_h