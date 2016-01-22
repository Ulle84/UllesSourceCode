#ifndef MYCLASS_H
#define MYCLASS_H

class MyClass
{
public:
  MyClass();

  void function();
  void anotherFunction();

private:
  class D;
  D* d;
};

#endif // MYCLASS_H
