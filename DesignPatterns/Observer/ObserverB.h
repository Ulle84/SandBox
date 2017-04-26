#ifndef OBSERVERB_H
#define OBSERVERB_H

#include "IObserver.h"

class ObserverB : public IObserver
{
public:
  ObserverB();
  ~ObserverB();

  // IObserver
  void notify();
};

#endif // OBSERVERB_H
