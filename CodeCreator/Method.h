#ifndef METHOD_H
#define METHOD_H

#include <QList>
#include <QString>

#include "Parameter.h"

class Method : public QList<Parameter>
{
public:
  Method();
  Method(const QString& methodDeclaration, const QString& implementationBody = QString());

  QString declaration(bool suppressVirtual = false) const;
  QString implementation(const QString& indent, const QString &className) const;

  bool isValid() const;

  enum Type
  {
    Normal,
    Virtual,
    PureVirtual
  };
  Type type() const;
  void setType(Type type);

  QString name() const;
  void setName(const QString& name);

  QString returnType() const;
  void setReturnType(const QString& returnType);

  enum DeclarationType
  {
    Public,
    Protected,
    Private
  };
  DeclarationType declarationType() const;
  void setDeclarationType(DeclarationType declarationType);

  void setImplementationBody(const QString& implementationBody);

private:
  QString m_name;
  QString m_returnType;
  QString m_implementationBody;
  Type m_type;
  DeclarationType m_declarationType;
};

#endif // METHOD_H
