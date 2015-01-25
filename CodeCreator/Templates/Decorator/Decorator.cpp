#include "Decorator.h"

Decorator::Decorator(IComponent *component) :
  mComponent(component)
{
}

Decorator::~Decorator()
{
}

//TODO Implementation