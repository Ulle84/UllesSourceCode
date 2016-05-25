#ifndef Test_h
#define Test_h

class Test
{
public:
  static Test* getInstance();

private:
  Test();
  Test(const Test& rhs){}
  Test(Test&& rhs){}
  Test& operator= (const Test& rhs){}
  Test& operator= (Test&& rhs){}
  ~Test(){}

  static Test* m_instance;
};

#endif // Test_h