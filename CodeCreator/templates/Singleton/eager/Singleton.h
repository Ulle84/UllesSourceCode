#ifndef SINGLETON_H
#define SINGLETON_H

class Singleton
{
public:
  static Singleton* getInstance();

private:
  Singleton();
  ~Singleton();
  Singleton(const Singleton& rhs);
  Singleton(Singleton&& rhs);
  Singleton& operator=(const Singleton& rhs);
    
  static Singleton* mInstance;
};

#endif // SINGLETON_H