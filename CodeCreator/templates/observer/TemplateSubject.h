#ifndef TEMPLATESUBJECT_H
#define TEMPLATESUBJECT_H

#include <vector>

#include "TemplateSubjectI.h"

class TemplateObserverI;

class TemplateSubject : public TemplateSubjectI
{
public:
  TemplateSubject();
  ~TemplateSubject();

  // TemplateSubjectI
  bool registerObserver(TemplateObserverI* observer);
  bool unregisterObserver(TemplateObserverI* observer);
  void notifyObservers();

private:
  std::vector<TemplateObserverI*> mObservers;
};

#endif // TEMPLATESUBJECT_H