#ifndef MYCLASS_H
#define MYCLASS_H

class MyClass
{
public:
  MyClass();
  ~MyClass();
  // TODO copy constructor etc.

  int value() const;
  void setValue(int value);
  void printValue() const;

private:
  class MyClassPrivate;
  MyClassPrivate* d; // here we have the D-Pointer
};

#endif // MYCLASS_H
