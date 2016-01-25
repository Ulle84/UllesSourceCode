#include "MyClass.h"

int main()
{
  MyClass myClass;
  myClass.setValue(100);

  MyClass myClass2(myClass);
  myClass2.printValue();

  MyClass myClass3;
  myClass3.printValue();

  myClass3 = myClass;
  myClass3.printValue();

  return 0;
}
