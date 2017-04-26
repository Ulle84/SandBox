#include <iostream>

#include "Base.h"

class Base::BasePrivate
{
public:
  BasePrivate() { std::cout << "construction of Base::BasePrivate" << std::endl; }

  int value;
};

Base::Base() :
  d(new Base::BasePrivate())
{
  d->value = 42;
}

Base::Base(const Base& rhs) :
  d(new Base::BasePrivate())
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
