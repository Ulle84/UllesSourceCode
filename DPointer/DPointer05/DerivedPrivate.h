#ifndef DERIVED_PRIVATE_H
#define DERIVED_PRIVATE_H

class DerivedPrivate
{
public:
  DerivedPrivate(Derived* derived) : derived(derived)
  {
    std::cout << "construction of DerivedPrivate" << std::endl;
  }

  Derived* derived;
  bool flag;
};

#endif // DERIVED_PRIVATE_H
