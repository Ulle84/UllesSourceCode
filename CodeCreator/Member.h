#ifndef Member_h
#define Member_h

#include "Parameter.h"

class Member : public Parameter
{
public:
  Member();
  ~Member();

  enum DeclarationType
  {
    Public,
    Protected,
    Private
  };
  DeclarationType declarationType() const;
  void setDeclarationType(DeclarationType declarationType);

private:
  DeclarationType m_declarationType;
};

#endif // Member_h
