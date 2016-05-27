#ifndef METHOD_H
#define METHOD_H

#include "Function.h"

class Method : public Function
{
public:
  Method();

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

#endif // METHOD_H
