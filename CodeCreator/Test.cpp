#include "Test.h"

Test* Test::horst_instance = nullptr;

Test* Test::getInstance()
{
  horst_mutex.lock();

  if (horst_instance == nullptr)
  {
    horst_instance = new Test();
  }

  horst_mutex.unlock();

  return horst_instance;
}
