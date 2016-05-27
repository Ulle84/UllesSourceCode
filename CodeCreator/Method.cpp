#include "Method.h"

Method::Method()
{

}

Method::DeclarationType Method::declarationType() const
{
  return m_declarationType;
}

void Method::setDeclarationType(DeclarationType declarationType)
{
  m_declarationType = declarationType;
}
