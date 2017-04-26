#include <iostream>

#include "BasePrivate.h"
#include "Derived.h"

// inheritance also at D-Pointer classes
class DerivedPrivate : public BasePrivate
{
public:
  bool flag;
};

// we use the D-Pointer of the base class
Derived::Derived() :
  Base(*new DerivedPrivate)
{
}

// alow subclasses of Derived to acces Base-D-Pointer
Derived::Derived(DerivedPrivate& d) :
  Base(d)
{

}

Derived::~Derived()
{
  // cleaning up D-Pointer is done in base class
}

bool Derived::flag() const
{
  // cast is needed, since 'd' has the type 'BasePrivate'
  DerivedPrivate* dp = static_cast<DerivedPrivate*>(d);
  return dp->flag;
}

Derived::Derived(const Derived& rhs) :
  Base(rhs)
{
  DerivedPrivate* dp = static_cast<DerivedPrivate*>(d);
  DerivedPrivate* dpRhs = static_cast<DerivedPrivate*>(rhs.d);

  dp->flag = dpRhs->flag;
}

Derived& Derived::operator=(const Derived& rhs)
{
  if (this != &rhs)
  {
    Base::operator=(rhs);

    DerivedPrivate* dp = static_cast<DerivedPrivate*>(d);
    DerivedPrivate* dpRhs = static_cast<DerivedPrivate*>(rhs.d);

    dp->flag = dpRhs->flag;
  }

  return *this;
}

void Derived::setFlag(bool flag)
{
  DerivedPrivate* dp = static_cast<DerivedPrivate*>(d);
  dp->flag = flag;
}

void Derived::printFlag() const
{
  DerivedPrivate* dp = static_cast<DerivedPrivate*>(d);
  std::cout << "flag: " << (dp->flag ? "on" : "off") << std::endl;
}
