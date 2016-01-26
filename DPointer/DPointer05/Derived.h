#ifndef DERIVED_H
#define DERIVED_H

#include "Base.h"

class DerivedPrivate;

class Derived : public Base
{
public:
  Derived();
  ~Derived();

  Derived(const Derived& rhs);
  Derived& operator=(const Derived& rhs);

  bool flag() const;
  void setFlag(bool flag);
  void printFlag() const;

protected:
  Derived(DerivedPrivate& d);
};

#endif // DERIVED_H