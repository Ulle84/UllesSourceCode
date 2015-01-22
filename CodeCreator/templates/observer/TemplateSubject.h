#ifndef TEMPLATESUBJECT_H
#define TEMPLATESUBJECT_H

#include <vector>

#include "TemplateObserverInterface.h"
#include "TemplateSubjectInterface.h"

class TemplateSubject : public TemplateSubjectInterface
{
public:
  TemplateSubject();
  ~TemplateSubject();

  // TemplateSubjectInterface
  bool registerObserver(TemplateObserverInterface* observer);
  bool unregisterObserver(TemplateObserverInterface* observer);
  void notifyObservers();

private:
  std::vector<TemplateObserverInterface*> m_observers;
};

#endif // TEMPLATESUBJECT_H