#ifndef SINGLETONEAGER_H
#define SINGLETONEAGER_H

#include <QString>

class SingletonEager
{
public:
  static SingletonEager* getInstance();
  QString sayHello();

private:
  SingletonEager();
  ~SingletonEager();
  SingletonEager(const SingletonEager& rhs);
  SingletonEager(SingletonEager&& rhs);
  SingletonEager& operator=(const SingletonEager& rhs);
    
  static SingletonEager* mInstance;
};

#endif // SINGLETONEAGER_H
