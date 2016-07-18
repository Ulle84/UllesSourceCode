#include <QDebug>

#include "Method.h"

Method::Method()
{

}

Method::Method(const QString& methodDeclaration, const QString& implementationBody)
{
  m_implementationBody = implementationBody;

  QString copy = methodDeclaration;
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
  QString code;

  if (m_type != Type::Normal && !suppressVirtual)
  {
    code.append("virtual ");
  }

  code.append(m_returnType);
  code.append(" ");
  code.append(m_name);
  code.append("(");

  for (auto it = begin(); it != end(); it++)
  {
    if (it != begin())
    {
      code.append(", ");
    }
    code.append(it->toString());
  }

  code.append(")");

  if (m_type == Type::PureVirtual && !suppressVirtual)
  {
    code.append(" = 0");
  }

  code.append(";");

  return code;
}

QString Method::implementation(const QString& indent, const QString& className) const
{
  QString code = indent;

  code.append(m_returnType);
  code.append(" ");
  code.append(className);
  code.append("::");
  code.append(m_name);
  code.append("(");

  for (auto it = begin(); it != end(); it++)
  {
    if (it != begin())
    {
      code.append(", ");
    }
    code.append(it->toString(true));
  }

  code.append(")\n");
  code.append(indent);
  code.append("{\n");

  if (!m_implementationBody.isEmpty())
  {
    QStringList splitted = m_implementationBody.split('\n');

    for (auto it = splitted.begin(); it != splitted.end(); it++)
    {
      if (it != splitted.begin())
      {
        code.append("\n");
      }

      code.append(indent);
      code.append("  ");
      code.append(*it);      
    }
  }

  code.append("\n");
  code.append(indent);
  code.append("}");

  return code;
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

void Method::setImplementationBody(const QString &implementationBody)
{
  m_implementationBody = implementationBody;
}
