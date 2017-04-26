#ifndef MYCLASS_H
#define MYCLASS_H

class MyClass // "overlaying" class
{
public:
  MyClass();
  ~MyClass();
  // TODO copy constructor and copy operator

  int value() const;
  void setValue(int value);
  void printValue() const;

private:
  class MyClassPrivate; // foward declaration to "underlaying" private class in private section -> no pollution of namespace
  MyClassPrivate* d; // here we have the D-Pointer
};

#endif // MYCLASS_H
