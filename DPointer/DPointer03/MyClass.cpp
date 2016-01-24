#include <QDebug>

#include "MyClass.h"

class MyClass::D
{
public:
  D(MyClass* myClass) : myClass(myClass) {}

  void function();

  MyClass* myClass;
  int value;
  bool flag;
};

void MyClass::D::function()
{
  qDebug() << "MyClass::D::function()";
  myClass->anotherFunction();
}

MyClass::MyClass() :
  d(new MyClass::D(this))
{
  d->flag = true;
  d->value = 42;
}

MyClass::~MyClass()
{
  delete d;
}

MyClass::MyClass(const MyClass &rhs) :
  d(new MyClass::D(this))
{
  d->flag = rhs.d->flag;
  d->value = rhs.d->value;
}

void MyClass::function()
{
  qDebug() << "MyClass::function()";
  d->function();
}

void MyClass::anotherFunction()
{
  qDebug() << "MyClass::anotherFunction()";
}
