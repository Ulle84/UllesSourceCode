#include <QDebug>

#include "Function.h"

Function::Function(const QString &function)
{
  QString copy = function;
  copy.replace(";", "");
  copy.replace("=", " = ");
  copy = copy.simplified();

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
        m_parameters.append(parameter);
      }
    }
  }

  Parameter parameter(copy.left(leftPos - 1));
  m_name = parameter.name();
  m_returnType = parameter.type();
}

QString Function::toString()
{
  QString function;

  if (m_type != Type::Normal)
  {
    function.append("virtual ");
  }

  function.append(m_returnType);
  function.append(" ");
  function.append(m_name);
  function.append("(");

  for (auto it = m_parameters.begin(); it != m_parameters.end(); it++)
  {
    if (it != m_parameters.begin())
    {
      function.append(", ");
    }
    function.append(it->toString());
  }

  function.append(")");

  if (m_type == Type::PureVirtual)
  {
    function.append(" = 0");
  }

  function.append(";");

  return function;
}
