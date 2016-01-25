#include "MyClass.h"

int main()
{
  MyClass myClass;
  myClass.setValue(100);

  MyClass myClass2(myClass);
  myClass2.printValue();
}
