#ifndef Declarations_h
#define Declarations_h

#include <QList>

#include "Declaration.h"

class Declarations : public QList<Declaration>
{
public:
  Declarations();
  ~Declarations();

  bool hasPublicDeclarations();
  bool hasProtectedDeclarations();
  bool hasPrivateDeclarations();

  QList<Declaration> publicDeclarations();
  QList<Declaration> protectedDeclarations();
  QList<Declaration> privateDeclarations();

private:
  bool hasDeclarationType(Declaration::DeclarationType declarationType);
  QList<Declaration> declarations(Declaration::DeclarationType declarationType);
};

#endif // Declarations_h
