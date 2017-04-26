#include <iostream>

#include "Derived.h"

class Derived::DerivedPrivate
{
public:
  DerivedPrivate() { std::cout << "construction of Derived::DerivedPrivate" << std::endl; }

  bool flag;
};

Derived::Derived() :
  d(new Derived::DerivedPrivate())
{
  d->flag = true;
}

Derived::~Derived()
{
  delete d;
}

Derived::Derived(const Derived& rhs) :
  Base(rhs),
  d(new Derived::DerivedPrivate())
{
  d->flag = rhs.d->flag;
}

Derived& Derived::operator=(const Derived& rhs)
{
  if (this != &rhs)
  {
    Base::operator=(rhs);
    d->flag = rhs.d->flag;
  }

  return *this;
}

bool Derived::flag() const
{
  return d->flag;
}

void Derived::setFlag(bool flag)
{
  d->flag = flag;
}

void Derived::printFlag() const
{
  std::cout << "flag: " << (d->flag ? "on" : "off") << std::endl;
}
