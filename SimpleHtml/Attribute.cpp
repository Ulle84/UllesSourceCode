#include "Attribute.h"

Attribute::Attribute()
{

}

Attribute::Attribute(const QString &name, const QString &value) :
  m_name(name),
  m_value(value)
{

}

bool Attribute::isValid()
{
  return !(m_name.isEmpty() || m_value.isEmpty());
}

QString Attribute::name()
{
  return m_name;
}

void Attribute::setName(const QString &name)
{
  m_name = name;
}

QString Attribute::value()
{
  return m_value;
}

void Attribute::setValue(const QString &value)
{
  m_value = value;
}
