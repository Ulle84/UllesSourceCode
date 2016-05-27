#ifndef Test_h
#define Test_h

#include <QtCore\QMutex>

class Test
{
public:
  static Test* getInstance();

private:
  Test();
  Test(const Test& rhs){}
  Test& operator= (const Test& rhs){}
  ~Test(){}

  static QMutex horst_mutex;
  static Test* horst_instance;
};

#endif // Test_h