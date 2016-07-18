#ifndef TemplateSubjectI_H
#define TemplateSubjectI_H

class TemplateObserverI;

class TemplateSubjectI
{
public:
  virtual ~TemplateSubjectI(){};

  virtual bool registerObserver(TemplateObserverI* observer) = 0;
  virtual bool unregisterObserver(TemplateObserverI* observer) = 0;
  virtual void notifyObservers() = 0;
};

#endif // TemplateSubjectI_H