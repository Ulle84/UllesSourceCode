#ifndef DECORATOR_H
#define DECORATOR_H

#include "IComponent.h"

class Decorator : public IComponent
{
public:
  Decorator(IComponent* component);
  ~Decorator();

  // IComponent
    
private:
  IComponent* mComponent;
};

#endif // DECORATOR_H
