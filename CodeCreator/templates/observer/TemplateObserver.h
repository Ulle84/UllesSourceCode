#ifndef TEMPLATEOBSERVER_H
#define TEMPLATEOBSERVER_H

#include "ITemplateObserver.h"

class TemplateObserver : public ITemplateObserver
{
public:
  TemplateObserver();
  ~TemplateObserver();
  
  // ITemplateObserver
  void notify();
};

#endif // TEMPLATEOBSERVER_H