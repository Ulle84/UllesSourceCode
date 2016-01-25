#include <iostream>

#include "BasePrivate.h"
#include "Derived.h"

class DerivedPrivate : public BasePrivate
{
public:
  bool flag;
};

Derived::Derived() :
  Base(*new DerivedPrivate)
{
}

Derived::Derived(DerivedPrivate& d) :
  Base(d)
{

}

Derived::~Derived()
{
}

Derived::Derived(const Derived& rhs) :
  Base(*new DerivedPrivate)
{
  DerivedPrivate* dp = static_cast<DerivedPrivate*>(d);
  DerivedPrivate* dpRhs = static_cast<DerivedPrivate*>(rhs.d);

  dp->value = dpRhs->value;
  dp->flag = dpRhs->flag;
}

Derived& Derived::operator=(const Derived& rhs)
{
  if (this != &rhs)
  {
    DerivedPrivate* dp = static_cast<DerivedPrivate*>(d);
    DerivedPrivate* dpRhs = static_cast<DerivedPrivate*>(rhs.d);

    dp->value = dpRhs->value;
    dp->flag = dpRhs->flag;
  }

  return *this;
}

bool Derived::flag() const
{
  DerivedPrivate* dp = static_cast<DerivedPrivate*>(d);
  return dp->flag;
}

void Derived::setFlag(bool flag)
{
  DerivedPrivate* dp = static_cast<DerivedPrivate*>(d);
  dp->flag = flag;
}

void Derived::printFlag() const
{
  DerivedPrivate* dp = static_cast<DerivedPrivate*>(d);
  std::cout << "flag: " << (dp->flag ? "on" : "off") << std::endl;
}
