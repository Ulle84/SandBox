#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

#include "ISubject.h"

class IObserver;

class Subject : public ISubject
{
public:
  Subject();
  ~Subject();

  // ISubject
  bool registerObserver(IObserver* observer);
  bool unregisterObserver(IObserver* observer);
  void notifyObservers();

private:
  std::vector<IObserver*> mObservers;
};

#endif // SUBJECT_H