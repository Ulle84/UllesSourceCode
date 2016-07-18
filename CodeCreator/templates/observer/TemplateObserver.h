#ifndef TEMPLATEOBSERVER_H
#define TEMPLATEOBSERVER_H

#include "TemplateObserverI.h"

class TemplateObserver : public TemplateObserverI
{
public:
  TemplateObserver();
  ~TemplateObserver();
  
  // TemplateObserverI
  void notify();
};

#endif // TEMPLATEOBSERVER_H