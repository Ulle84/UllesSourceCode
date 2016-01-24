#ifndef MYCLASS_H
#define MYCLASS_H

class MyClass
{
public:
  MyClass();
  ~MyClass();

  MyClass(const MyClass& rhs);

  void function();
  void anotherFunction();

private:
  class D;
  D* d;
};

#endif // MYCLASS_H
