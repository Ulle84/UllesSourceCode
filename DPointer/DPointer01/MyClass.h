#ifndef MYCLASS_H
#define MYCLASS_H

class MyClass
{
public:
  MyClass();
  ~MyClass();
  // TODO move constructor etc.

  int value() const;
  void setValue(int value);
  void printValue();

private:
  class D;
  D* d;
};

#endif // MYCLASS_H
