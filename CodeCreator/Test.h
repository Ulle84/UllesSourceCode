#ifndef Test_h
#define Test_h

#include "BaseClass.h"
#include "InterfaceA.h"
#include "InterfaceB.h"

class Test : public BaseClass, public InterfaceA, public InterfaceB
{
public:
  Test();
  ~Test();
};

#endif // Test_h