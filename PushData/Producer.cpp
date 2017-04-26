#include "Producer.h"

Producer::Producer()
{

}

void Producer::registerCallBack(void (*callBack)(int))
{
  m_callBack = callBack;
}

void Producer::run()
{
  for (int i = 0; i < 10; i++)
  {
    QThread::msleep(200);
    m_callBack(i);
  }
}
