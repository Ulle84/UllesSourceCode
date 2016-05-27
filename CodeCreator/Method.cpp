#include "Method.h"

Method::Method(const QString& method)
  : Function(method)
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
