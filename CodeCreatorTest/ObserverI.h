#ifndef ObserverI_h
#define ObserverI_h

class ObserverI
{
public:
  virtual ~ObserverI(){}

  virtual void notify() = 0;
};

#endif // ObserverI_h