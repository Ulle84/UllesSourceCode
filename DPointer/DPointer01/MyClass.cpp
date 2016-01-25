#include <iostream>

#include "MyClass.h"

class MyClass::MyClassPrivate
{
public:
  int value;
};

MyClass::MyClass() :
  d(new MyClass::MyClassPrivate())
{
  d->value = 42;
}

MyClass::~MyClass()
{
  delete d;
}

int MyClass::value() const
{
  return d->value;
}

void MyClass::setValue(int value)
{
  d->value = value;
}

void MyClass::printValue() const
{
  std::cout << "value: " << d->value << std::endl;
}

