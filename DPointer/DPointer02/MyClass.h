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
  void printValue() const;

  void reset();

  void update();

private:
  class MyClassPrivate;
  MyClassPrivate* d;
};

#endif // MYCLASS_H
