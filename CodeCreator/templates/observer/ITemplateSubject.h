#ifndef ITEMPLATESUBJECT_H
#define ITEMPLATESUBJECT_H

class ITemplateSubject
{
public:
  virtual bool registerObserver(TemplateObserverInterface* observer) = 0;
  virtual bool unregisterObserver(TemplateObserverInterface* observer) = 0;
  virtual void notifyObservers() = 0;
};

#endif // ITEMPLATESUBJECT_H