#include <algorithm>

#include "TemplateSubject.h"
#include "ITemplateObserver.h"

TemplateSubject::TemplateSubject()
{
}

TemplateSubject::~TemplateSubject()
{
}

bool TemplateSubject::registerObserver(ITemplateObserver* observer)
{
  bool returnValue = false;

  if (observer != nullptr)
  {
    if (std::find(mObservers.begin(), mObservers.end(), observer) == mObservers.end())
    {
      mObservers.push_back(observer);
      returnValue = true;
    }
  }

  return returnValue;
}

bool TemplateSubject::unregisterObserver(ITemplateObserver* observer)
{
  bool returnValue = false;

  if (observer != nullptr)
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

void TemplateSubject::notifyObservers()
{
  for (auto it = mObservers.begin(); it != mObservers.end(); it++)
  {
    (*it)->notify();
  }
}
