#ifndef METHOD_H
#define METHOD_H

#include <QList>
#include <QString>

#include "Parameter.h"

class Method : public QList<Parameter>
{
public:
  Method();
  Method(const QString& method);

  QString declaration(bool suppressVirtual = false) const;
  QString implementation(const QString& indent) const;

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

private:
  QString m_name;
  QString m_returnType;
  Type m_type;
  DeclarationType m_declarationType;

  friend class MethodGui;
};

#endif // METHOD_H
