#include <iostream>

#include "Base.h"

class Base::BasePrivate
{
public:
  BasePrivate(Base* base) : base(base)
  {
    std::cout << "construction of Base::BasePrivate" << std::endl;
  }

  void reset();

  Base* base;
  int value;
};

void Base::BasePrivate::reset()
{
  std::cout << "Base::BasePrivate::reset()" << std::endl;
  value = 42;
  base->update();
}

Base::Base() :
  d(new Base::BasePrivate(this))
{
  d->value = 42;
}

Base::Base(const Base& rhs) :
  d(new Base::BasePrivate(this))
{
  d->value = rhs.d->value;
}

Base& Base::operator=(const Base& rhs)
{
  if (this != &rhs)
  {
    d->value = rhs.d->value;
  }

  return *this;
}

Base::~Base()
{
  delete d;
}

int Base::value() const
{
  return d->value;
}

void Base::setValue(int value)
{
  d->value = value;
}

void Base::printValue() const
{
  std::cout << "value: " << d->value << std::endl;
}

void Base::reset()
{
  std::cout << "Base::reset()" << std::endl;
  d->reset();
}

void Base::update()
{
  std::cout << "Base::update()" << std::endl;
}