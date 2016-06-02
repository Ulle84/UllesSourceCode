#include "Interface.h"

#include <QSTringList>

Interface::Interface()
  : m_implementInterface(true)
{
}

Interface::Interface(const QString &name, const QString &interface)
  : m_implementInterface(true),
    m_name(name)
{
  QStringList methods = interface.split("\n");

  for (auto it = methods.begin(); it != methods.end(); it++)
  {
    Method method(*it);
    method.setType(Method::Type::PureVirtual);
    method.setDeclarationType(Method::DeclarationType::Public);
    if (method.isValid())
    {
      append(method);
    }
  }
}

QString Interface::name()
{
  return m_name;
}

void Interface::setName(const QString &name)
{
  m_name = name;
}

QString Interface::toString()
{
  QString interface;

  for (auto it = begin(); it != end(); it++)
  {
    if (it != begin())
    {
      interface.append("\n");
    }

    interface.append(it->declaration());
  }

  return interface;
}

bool Interface::isToImplement()
{
  return m_implementInterface;
}
