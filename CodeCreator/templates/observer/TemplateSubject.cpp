#include <algorithm>

#include "TemplateSubject.h"

TemplateSubject::TemplateSubject()
{
}

TemplateSubject::~TemplateSubject()
{
}

bool TemplateSubject::registerObserver( TemplateObserverInterface* observer )
{
  bool returnValue = false;

  if (observer != nullptr)
  {
    if (std::find(m_observers.begin(), m_observers.end(), observer) == m_observers.end())
    {
      m_observers.push_back(observer);
      returnValue = true;
    }
  }

  return returnValue;
}

bool TemplateSubject::unregisterObserver( TemplateObserverInterface* observer )
{
  bool returnValue = false;

  if (observer != nullptr)
  {
    for (auto iter = m_observers.begin(); iter != m_observers.end(); iter++)
    {
      if (*iter == observer)
      {
        m_observers.erase(iter);
        returnValue = true;
        break;
      }
    }
  }

  return returnValue;
}

void TemplateSubject::notifyObservers()
{
  for (auto iter = m_observers.begin(); iter != m_observers.end(); iter++)
  {
    (*iter)->notify();
  }
}
