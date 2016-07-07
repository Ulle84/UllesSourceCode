#include <QDebug>

#include "Method.h"

Method::Method()
{

}

Method::Method(const QString &method)
{
  QString copy = method;
  copy.replace(";", "");
  copy.replace("=", " = ");
  copy = copy.simplified();

  if (copy.startsWith("//"))
  {
    return;
  }

  if (copy.endsWith(" = 0") && copy.startsWith("virtual"))
  {
    m_type = Type::PureVirtual;
  }
  else if (copy.startsWith("virtual"))
  {
    m_type = Type::Virtual;
  }
  else
  {
    m_type = Type::Normal;
  }

  copy.replace(" = 0", "");
  copy.replace("virtual", "");

  int leftPos = copy.indexOf("(") + 1;
  int rightPos = copy.lastIndexOf(")");

  if (leftPos < rightPos)
  {
    QStringList parameters = copy.mid(leftPos, rightPos - leftPos).split(",");
    for (auto it = parameters.begin(); it != parameters.end(); it++)
    {
      Parameter parameter(*it);

      if (parameter.isValid())
      {
        append(parameter);
      }
    }
  }

  Parameter parameter(copy.left(leftPos - 1));
  m_name = parameter.name();
  m_returnType = parameter.type();
}

QString Method::declaration(bool suppressVirtual) const
{
  QString method;

  if (m_type != Type::Normal && !suppressVirtual)
  {
    method.append("virtual ");
  }

  method.append(m_returnType);
  method.append(" ");
  method.append(m_name);
  method.append("(");

  for (auto it = begin(); it != end(); it++)
  {
    if (it != begin())
    {
      method.append(", ");
    }
    method.append(it->toString());
  }

  method.append(")");

  if (m_type == Type::PureVirtual && !suppressVirtual)
  {
    method.append(" = 0");
  }

  method.append(";");

  return method;
}

QString Method::implementation(const QString& indent) const
{
  QString method = indent;

  method.append(m_returnType);
  method.append(" ");
  method.append(m_name);
  method.append("(");

  for (auto it = begin(); it != end(); it++)
  {
    if (it != begin())
    {
      method.append(", ");
    }
    method.append(it->toString(true));
  }

  method.append(")\n");
  method.append(indent);
  method.append("{\n\n");
  method.append(indent);
  method.append("}");

  return method;
}

bool Method::isValid() const
{
  return !m_name.isEmpty() && !m_returnType.isEmpty();
}

Method::Type Method::type() const
{
  return m_type;
}

void Method::setType(Method::Type type)
{
  m_type = type;
}

QString Method::name() const
{
  return m_name;
}

void Method::setName(const QString &name)
{
  m_name = name;
}

QString Method::returnType() const
{
  return m_returnType;
}

void Method::setReturnType(const QString &returnType)
{
  m_returnType = returnType;
}

Method::DeclarationType Method::declarationType() const
{
  return m_declarationType;
}

void Method::setDeclarationType(Method::DeclarationType declarationType)
{
  m_declarationType = declarationType;
}
