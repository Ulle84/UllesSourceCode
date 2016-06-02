#ifndef METHOD_H
#define METHOD_H

#include <QList>
#include <QString>

#include "Parameter.h"

class Method
{
public:
  Method();
  Method(const QString& method);

  QString declaration(bool suppressVirtual = false) const;

  bool isValid() const;

  enum Type
  {
    Normal,
    Virtual,
    PureVirtual
  };
  void setType(Type type);
  void setName(const QString& name);
  void setReturnType(const QString& returnType);

  enum DeclarationType
  {
    Public,
    Protected,
    Private
  };
  DeclarationType declarationType() const;
  void setDeclarationType(DeclarationType declarationType);

private:
  QString m_name;
  QString m_returnType;
  Type m_type;
  QList<Parameter> m_parameters;
  DeclarationType m_declarationType;

  friend class MethodGui;
};

#endif // METHOD_H
