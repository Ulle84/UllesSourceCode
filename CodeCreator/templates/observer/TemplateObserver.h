#ifndef TEMPLATEOBSERVER_H
#define TEMPLATEOBSERVER_H

#include "TemplateObserverInterface.h"

class TemplateObserver : public TemplateObserverInterface
{
public:
  TemplateObserver();
  ~TemplateObserver();
  
  // TemplateObserverInterface
  void notify();
};

#endif // TEMPLATEOBSERVER_H