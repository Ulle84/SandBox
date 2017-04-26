#ifndef BASE_H
#define BASE_H

class Base
{
public:
  Base();
  virtual ~Base();

  Base(const Base& rhs);
  Base& operator=(const Base& rhs);

  int value() const;
  void setValue(int value);
  void printValue() const;

private:
  class BasePrivate;
  BasePrivate* d;
};

#endif // BASE_H
