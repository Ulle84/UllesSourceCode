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
    if (std::find(m_observers.begin(), m_observers.end(), observer) == m_observers.end())
    {
      m_observers.push_back(observer);
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
    for (auto it = m_observers.begin(); it != m_observers.end(); it++)
    {
      if (*it == observer)
      {
        m_observers.erase(it);
        returnValue = true;
        break;
      }
    }
  }

  return returnValue;
}

void TemplateSubject::notifyObservers()
{
  for (auto it = m_observers.begin(); it != m_observers.end(); it++)
  {
    (*it)->notify();
  }
}
