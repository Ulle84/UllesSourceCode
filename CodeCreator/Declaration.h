#ifndef Declaration_h
#define Declaration_h

#include <QString>

class Declaration
{
public:
  Declaration();
  ~Declaration();

  QString declaration() const;
  void setDeclaration(const QString& declaration);

  enum DeclarationType
  {
    Public,
    Protected,
    Private
  };
  DeclarationType declarationType() const;
  void setDeclarationType(const DeclarationType& declarationType);

private:
  QString m_declaration;
  DeclarationType m_declarationType;
};

#endif // Declaration_h
