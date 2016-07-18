#ifndef SubjectI_h
#define SubjectI_h

class ObserverI;

class SubjectI
{
public:
  virtual ~SubjectI(){}

  virtual bool registerObserver(ObserverI* observer) = 0;
  virtual bool unregisterObserver(ObserverI* observer) = 0;
  virtual bool notifyObservers() = 0;
};

#endif // SubjectI_h