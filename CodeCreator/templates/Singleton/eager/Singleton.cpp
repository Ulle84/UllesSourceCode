#include "Singleton.h"

Singleton* Singleton::mInstance = new Singleton();

Singleton::Singleton()
{
}

Singleton::~Singleton()
{
}

Singleton* Singleton::getInstance()
{
  return mInstance;
}