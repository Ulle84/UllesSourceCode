#include "Derived.h"

int main()
{
  Derived derived;
  derived.setValue(123);
  derived.printValue();

  derived.setFlag(false);
  derived.printFlag();

  Derived derived2(derived);
  derived2.printValue();
  derived2.printFlag();

  return 0;
}
