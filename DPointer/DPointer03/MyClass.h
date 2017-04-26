#ifndef MYCLASS_H
#define MYCLASS_H

class MyClass
{
public:
  MyClass();
  ~MyClass();

  MyClass(const MyClass& rhs); // copy constructor
  MyClass& operator=(const MyClass& rhs); // copy operator

  int value() const;
  void setValue(int value);
  void printValue() const;

  void reset();

  void update();

private:
  class MyClassPrivate;
  MyClassPrivate* d;
};

#endif // MYCLASS_H
