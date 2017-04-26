#include <iostream>

#include "MyClass.h"

// the declaration of the "underlaying" D-Pointer class
class MyClass::MyClassPrivate
{
public:
  int value;
};

MyClass::MyClass() :
  d(new MyClass::MyClassPrivate()) // here the D-Pointer is initialized
{
  d->value = 42; // here a value of the D-Pointer class instance is set
}

MyClass::~MyClass()
{
  delete d; // don't forget to clean up
}

int MyClass::value() const
{
  return d->value;
}

void MyClass::setValue(int value)
{
  d->value = value;
}

void MyClass::printValue() const
{
  std::cout << "value: " << d->value << std::endl;
}

