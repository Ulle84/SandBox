#ifndef BASE_H
#define BASE_H

class BasePrivate; // cannot be declared private anymore and needs its own header

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

protected:
  Base(BasePrivate& d); // allow derived classes to initialize with their own D-Pointer
  BasePrivate* d; // not private anymore, but protected so it is accessible for derived classes

/* former version:
private:
  class BasePrivate;
  BasePrivate* d;
*/
};

#endif // BASE_H
