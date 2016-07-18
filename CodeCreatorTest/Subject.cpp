#include <QDebug>

#include <algorithm>
#include "ObserverI.h"

#include "Subject.h"

Subject::Subject()
{

}

Subject::~Subject()
{

}

bool Subject::registerObserver(ObserverI* observer)
{
  if (observer != 0)
  {
    if (std::find(m_observers.begin(), m_observers.end(), observer) == m_observers.end())
    {
      qDebug() << "register";
      m_observers.push_back(observer);
      return true;
    }
  }
  
  return false;
}

bool Subject::unregisterObserver(ObserverI* observer)
{
  if (observer != 0)
  {
    for (auto it = m_observers.begin(); it != m_observers.end(); it++)
    {
      if (*it == observer)
      {
        qDebug() << "unregister";
        m_observers.erase(it);
        return true;
      }
    }
  }
  
  return false;
  
}

bool Subject::notifyObservers()
{
  for (auto it = m_observers.begin(); it != m_observers.end(); it++)
  {

    qDebug() << "notify";
      (*it)->notify();


  }
}
