#ifndef Decorator_h
#define Decorator_h

#include "ComponentI.h"

class Decorator : public ComponentI
{
public:
  Decorator(ComponentI* component);
  ~Decorator();

  // ComponentI
    
private:
  ComponentI* m_component;
};

#endif // Decorator_h
