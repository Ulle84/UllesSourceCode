#ifndef FUNCTION_H
#define FUNCTION_H

#include <QList>
#include <QString>

#include "Parameter.h"

class Function
{
public:
  Function(const QString& function);

  QString toString() const;

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
};

#endif // FUNCTION_H
