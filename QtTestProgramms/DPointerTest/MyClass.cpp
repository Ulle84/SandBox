#include <QDebug>

#include "MyClass.h"

class MyClass::D
{
public:
  D(MyClass* myClass) : myClass(myClass) {}

  void function();

  MyClass* myClass;
  int i;
  bool b;
};

void MyClass::D::function()
{
  qDebug() << "MyClass::D::function()";
  myClass->anotherFunction();
}

MyClass::MyClass() :
  d(new MyClass::D(this))
{
  d->b = true;
}

MyClass::~MyClass()
{
  delete d;
}

void MyClass::function()
{
  qDebug() << "MyClass::function()";
  d->function();
}

void MyClass::anotherFunction()
{
  qDebug() << "MyClass::anotherFunction()";
}
