#ifndef DECORATORA_H
#define DECORATORA_H

#include "Decorator.h"

class DecoratorA : public Decorator
{
public:
  DecoratorA(IComponent* component);
  ~DecoratorA();
};

#endif // DECORATORA_H
