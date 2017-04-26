#ifndef ISUBJECT_H
#define ISUBJECT_H

class IObserver;

class ISubject
{
public:
  virtual bool registerObserver(IObserver* observer) = 0;
  virtual bool unregisterObserver(IObserver* observer) = 0;
  virtual void notifyObservers() = 0;
};

#endif // ISUBJECT_H
