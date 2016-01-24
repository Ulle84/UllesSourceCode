#include <QDebug>

#include "MyClass.h"

class MyClass::D
{
public:
  int value;
};

MyClass::MyClass() :
  d(new MyClass::D())
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

void MyClass::printValue()
{
  qDebug() << "value:" << d->value;
}

