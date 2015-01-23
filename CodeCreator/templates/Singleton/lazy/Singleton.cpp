#include "Singleton.h"

Singleton* Singleton::mInstance = nullptr;

Singleton::Singleton()
{
}

Singleton::~Singleton()
{
}

Singleton* Singleton::getInstance()
{
  mMutex.lock();
  if(mInstance == nullptr)
  {
    mInstance = new Singleton();
  }
  mMutex.unlock();
  return mInstance;
}