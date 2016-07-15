#include "Declaration.h"

Declaration::Declaration() :
  m_declarationType(DeclarationType::Public)
{

}

Declaration::~Declaration()
{

}

QString Declaration::declaration() const
{
  return m_declaration;
}

void Declaration::setDeclaration(const QString& declaration)
{
  m_declaration = declaration;
}

Declaration::DeclarationType Declaration::declarationType() const
{
  return m_declarationType;
}

void Declaration::setDeclarationType(const DeclarationType& declarationType)
{
  m_declarationType = declarationType;
}
