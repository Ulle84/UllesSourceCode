#ifndef SINGLETON_H
#define SINGLETON_H

#include <QMutex>

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
    
  static QMutex mMutex;
  static Singleton* mInstance;
};

#endif // SINGLETON_H