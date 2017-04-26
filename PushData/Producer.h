#ifndef PRODUCER_H
#define PRODUCER_H

#include <QThread>

class Producer : public QThread
{
  Q_OBJECT

public:
  Producer();

  void registerCallBack(void (*callBack)(int));
  void run();

private:
  void (*m_callBack)(int);
};

#endif // PRODUCER_H
