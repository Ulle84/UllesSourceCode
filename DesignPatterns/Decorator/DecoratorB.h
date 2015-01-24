#ifndef DECORATORB_H
#define DECORATORB_H

#include "Decorator.h"

class DecoratorB : public Decorator
{
public:
  DecoratorB(IComponent* component);
  ~DecoratorB();
};

#endif // DECORATORB_H
