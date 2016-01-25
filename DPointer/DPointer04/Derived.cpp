#include <iostream>

#include "Derived.h"

class Derived::DerivedPrivate
{
public:
  DerivedPrivate(Derived* derived) : derived(derived) {std::cout << "construction of Derived::DerivedPrivate" << std::endl;}

  Derived* derived;
  bool flag;
};

Derived::Derived() :
  d(new Derived::DerivedPrivate(this))
{
  d->flag = true;
}

Derived::~Derived()
{
  delete d;
}

Derived::Derived(const Derived& rhs) :
  d(new Derived::DerivedPrivate(this))
{
  d->flag = rhs.d->flag;
}

Derived& Derived::operator=(const Derived &rhs)
{
  if(this != &rhs)
  {
    d->flag = rhs.d->flag;
  }
  return *this;
}

bool Derived::flag() const
{
  return d->flag;
}

void Derived::setFlag(bool flag)
{
  d->flag = flag;
}

void Derived::printFlag() const
{
  std::cout << "flag: " << (d->flag ? "on" : "off") << std::endl;
}
