#ifndef CONTEXT_H
#define CONTEXT_H

#include "IState.h"

class Context : public IState
{
public:
  Context();
  ~Context();
    
  // IState
    
private:
    IState* mState;
};

#endif // CONTEXT_H