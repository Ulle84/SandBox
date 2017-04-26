#include <algorithm>

#include "Subject.h"
#include "IObserver.h"

Subject::Subject()
{
}

Subject::~Subject()
{
}

bool Subject::registerObserver(IObserver* observer)
{
  bool returnValue = false;

  if (observer != 0)
  {
    if (std::find(mObservers.begin(), mObservers.end(), observer) == mObservers.end())
    {
      mObservers.push_back(observer);
      returnValue = true;
    }
  }

  return returnValue;
}

bool Subject::unregisterObserver(IObserver* observer)
{
  bool returnValue = false;

  if (observer != 0)
  {
    for (auto it = mObservers.begin(); it != mObservers.end(); it++)
    {
      if (*it == observer)
      {
        mObservers.erase(it);
        returnValue = true;
        break;
      }
    }
  }

  return returnValue;
}

void Subject::notifyObservers()
{
  for (auto it = mObservers.begin(); it != mObservers.end(); it++)
  {
    (*it)->notify();
  }
}
