#include "Declarations.h"

Declarations::Declarations()
{

}

Declarations::~Declarations()
{

}

bool Declarations::hasPublicDeclarations()
{
  return hasDeclarationType(Declaration::DeclarationType::Public);
}

bool Declarations::hasProtectedDeclarations()
{
  return hasDeclarationType(Declaration::DeclarationType::Protected);
}

bool Declarations::hasPrivateDeclarations()
{
  return hasDeclarationType(Declaration::DeclarationType::Private);
}

QList<Declaration> Declarations::publicDeclarations()
{
  return declarations(Declaration::DeclarationType::Public);
}

QList<Declaration> Declarations::protectedDeclarations()
{
return declarations(Declaration::DeclarationType::Protected);
}

QList<Declaration> Declarations::privateDeclarations()
{
return declarations(Declaration::DeclarationType::Private);
}

bool Declarations::hasDeclarationType(Declaration::DeclarationType declarationType)
{
  for (auto it = begin(); it != end(); it++)
  {
    if (it->declarationType() == declarationType)
    {
      return true;
    }
  }

  return false;
}

QList<Declaration> Declarations::declarations(Declaration::DeclarationType declarationType)
{
  QList<Declaration> declarations;

  for (auto it = begin(); it != end(); it++)
  {
    if (it->declarationType() == declarationType)
    {
      declarations.append(*it);
    }
  }

  return declarations;
}
