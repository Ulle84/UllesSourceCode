#include <QDebug>

#include "Parameter.h"

Parameter::Parameter(const QString &type, const QString &name, const QString &defaultValue)
  : m_type(type),
    m_name(name),
    m_defaultValue(defaultValue)
{
}

Parameter::Parameter(const QString &parameter)
{
  QString copy = parameter;

  copy.replace("=", " = ");
  copy.replace("*", " * ");
  copy.replace("&", " & ");

  copy = copy.simplified();

  copy.replace(" &", "&");
  copy.replace(" *", "*");

  if (copy.contains(" = "))
  {
    QStringList splitted = copy.split(" = ");
    m_defaultValue = splitted.last();
    copy = splitted.first();
  }

  QStringList splitted = copy.split(" ");
  m_name = splitted.last();

  splitted.removeLast();
  m_type = splitted.join(" ");
}

bool Parameter::isValid()
{
  return !m_type.isEmpty() && !m_name.isEmpty();
}

QString Parameter::toString()
{
  QString parameter;
  parameter.append(m_type);
  parameter.append(" ");
  parameter.append(m_name);

  if (!m_defaultValue.isEmpty())
  {
    parameter.append(" = ");
    parameter.append(m_defaultValue);
  }

  return parameter;
}

QString Parameter::type()
{
  return m_type;
}

QString Parameter::name()
{
  return m_name;
}

QString Parameter::defaultValue()
{
  return m_defaultValue;
}
