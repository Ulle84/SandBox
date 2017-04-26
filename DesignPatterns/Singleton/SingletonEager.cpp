#include "SingletonEager.h"

SingletonEager* SingletonEager::mInstance = new SingletonEager();

SingletonEager::SingletonEager()
{
}

SingletonEager::~SingletonEager()
{
}

SingletonEager* SingletonEager::getInstance()
{
  return mInstance;
}

QString SingletonEager::sayHello()
{
  return QString("Hello, I am the eager Singleton - I am the only one!");
}
