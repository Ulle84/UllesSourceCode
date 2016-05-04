#ifndef ITEMPLATESUBJECT_H
#define ITEMPLATESUBJECT_H

class ITemplateObserver;

class ITemplateSubject
{
public:
  virtual ~ITemplateSubject(){};

  virtual bool registerObserver(ITemplateObserver* observer) = 0;
  virtual bool unregisterObserver(ITemplateObserver* observer) = 0;
  virtual void notifyObservers() = 0;
};

#endif // ITEMPLATESUBJECT_H