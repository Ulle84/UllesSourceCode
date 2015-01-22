#ifndef TEMPLATESUBJECTINTERFACE_H
#define TEMPLATESUBJECTINTERFACE_H

class TemplateSubjectInterface
{
public:
  virtual bool registerObserver(TemplateObserverInterface* observer) = 0;
  virtual bool unregisterObserver(TemplateObserverInterface* observer) = 0;
  virtual void notifyObservers() = 0;
};

#endif // TEMPLATESUBJECTINTERFACE_H