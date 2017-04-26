#ifndef OBSERVERA_H
#define OBSERVERA_H

#include "IObserver.h"

class ObserverA : public IObserver
{
public:
  ObserverA();
  ~ObserverA();

  // IObserver
  void notify();
};

#endif // OBSERVERA_H
