#ifndef Observer_h
#define Observer_h

#include "ObserverI.h"

class Observer : public ObserverI
{
public:
  Observer(const QString& id);
  ~Observer();

  // interface ObserverI
  void notify();

private:
  QString m_id;
};

#endif // Observer_h
