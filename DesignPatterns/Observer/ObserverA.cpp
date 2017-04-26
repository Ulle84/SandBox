#include <QDebug>

#include "ObserverA.h"

ObserverA::ObserverA()
{
}

ObserverA::~ObserverA()
{
}

void ObserverA::notify()
{
  qDebug() << "observer A was notified";
}
