#ifndef Subject_h
#define Subject_h

#include "SubjectI.h"

#include <vector>

class ObserverI;

class Subject : public SubjectI
{
public:
  Subject();
  ~Subject();

  // interface SubjectI
  bool registerObserver(ObserverI* observer);
  bool unregisterObserver(ObserverI* observer);
  bool notifyObservers();

private:
  std::vector<ObserverI*> m_observers;
};

#endif // Subject_h
