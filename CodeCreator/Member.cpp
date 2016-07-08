#include "Member.h"

Member::Member()
{

}

Member::~Member()
{

}

QString Member::type() const
{
  return m_type;
}

void Member::setType(const QString &type)
{
  m_type = type;
}

QString Member::name() const
{
  return m_name;
}

void Member::setName(const QString &name)
{
  m_name = name;
}

QString Member::defaultValue() const
{
  return m_defaultValue;
}

void Member::setDefaultValue(const QString &defaultValue)
{
  m_defaultValue = defaultValue;
}

Member::DeclarationType Member::declarationType() const
{
  return m_declarationType;
}

void Member::setDeclarationType(Member::DeclarationType declarationType)
{
  m_declarationType = declarationType;
}
