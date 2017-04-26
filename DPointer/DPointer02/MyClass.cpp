#include <iostream>

#include "MyClass.h"

class MyClass::MyClassPrivate
{
public:
  // "underlaying" D-Pointer Class is initialized with pointer of "overlaying" class
  MyClassPrivate(MyClass* myClass) : myClass(myClass) {}

  void reset();

  MyClass* myClass;
  int value;
};

void MyClass::MyClassPrivate::reset()
{
  std::cout << "MyClass::MyClassPrivate::reset()" << std::endl;
  value = 42;
  myClass->update(); // here we can access the "overlaying" class
}

MyClass::MyClass() :
  d(new MyClass::MyClassPrivate(this)) // initialization of D-Pointer with 'this'
{
  d->value = 42;
}

MyClass::~MyClass()
{
  delete d;
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

void MyClass::reset()
{
  std::cout << "MyClass::reset()" << std::endl;
  d->reset();
}

void MyClass::update()
{
  std::cout << "MyClass::update()" << std::endl;
}
