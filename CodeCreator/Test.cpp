#include "Test.h"

Test* Test::m_instance = new Test();

Test* Test::getInstance()
{
  return m_instance;
}
