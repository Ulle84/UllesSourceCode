#ifndef TemplateObserverI_H
#define TemplateObserverI_H

class TemplateObserverI
{
public:
  virtual ~TemplateObserverI(){};

  virtual void notify() = 0;
};

#endif // TemplateObserverI_H