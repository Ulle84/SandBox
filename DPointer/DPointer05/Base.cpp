#include <iostream>

#include "Base.h"
#include "BasePrivate.h"

Base::Base() :
  d(new BasePrivate())
{
  d->value = 42;
}

// this protected constructor is new
Base::Base(BasePrivate& d) :
  d(&d)
{

}

Base::Base(const Base& rhs) :
  d(new BasePrivate())
{
  d->value = rhs.d->value;
}

Base& Base::operator=(const Base& rhs)
{
  if (this != &rhs)
  {
    d->value = rhs.d->value;
  }

  return *this;
}

Base::~Base()
{
  delete d;
}

int Base::value() const
{
  return d->value;
}

void Base::setValue(int value)
{
  d->value = value;
}

void Base::printValue() const
{
  std::cout << "value: " << d->value << std::endl;
}
