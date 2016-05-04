#ifndef ITEMPLATEOBSERVER_H
#define ITEMPLATEOBSERVER_H

class ITemplateObserver
{
public:
  virtual ~ITemplateObserver(){};

  virtual void notify() = 0;
};

#endif // ITEMPLATEOBSERVER_H