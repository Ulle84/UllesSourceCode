#include "Decorator.h"

Decorator::Decorator(ComponentI *component) :
  m_component(component)
{
}

Decorator::~Decorator()
{
}

//TODO Implementation Decorator