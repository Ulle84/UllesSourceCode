#include <QDebug>

#include "Parameter.h"

Parameter::Parameter()
{

}

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

bool Parameter::isValid() const
{
  return !m_type.isEmpty() && !m_name.isEmpty();
}

QString Parameter::toString(bool suppressDefaultValue) const
{
  QString parameter;
  parameter.append(m_type);
  parameter.append(" ");
  parameter.append(m_name);

  if (!m_defaultValue.isEmpty() && !suppressDefaultValue)
  {
    parameter.append(" = ");
    parameter.append(m_defaultValue);
  }

  return parameter;
}

QString Parameter::type() const
{
  return m_type;
}

void Parameter::setType(const QString& type)
{
  m_type = type;
}

QString Parameter::name() const
{
  return m_name;
}

void Parameter::setName(const QString& name)
{
  m_name = name;
}

QString Parameter::defaultValue() const
{
  return m_defaultValue;
}

void Parameter::setDefaultValue(const QString& defaultValue)
{
  m_defaultValue = defaultValue;
}
