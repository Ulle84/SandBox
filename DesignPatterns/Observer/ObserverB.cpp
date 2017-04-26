#include <QDebug>

#include "ObserverB.h"

ObserverB::ObserverB()
{
}

ObserverB::~ObserverB()
{
}

void ObserverB::notify()
{
  qDebug() << "observer B was notified";
}
