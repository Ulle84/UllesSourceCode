#ifndef TEMPLATESUBJECT_H
#define TEMPLATESUBJECT_H

#include <vector>

#include "ITemplateSubject.h"

class ITemplateObserver;

class TemplateSubject : public ITemplateSubject
{
public:
  TemplateSubject();
  ~TemplateSubject();

  // ITemplateSubject
  bool registerObserver(ITemplateObserver* observer);
  bool unregisterObserver(ITemplateObserver* observer);
  void notifyObservers();

private:
  std::vector<ITemplateObserver*> m_observers;
};

#endif // TEMPLATESUBJECT_H