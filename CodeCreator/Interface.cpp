#include "Interface.h"

#include <QSTringList>

Interface::Interface()
{
}

Interface::Interface(const QString &name, const QString &interface)
{
  m_name = name;

  QStringList functions = interface.split("\n");

  for (auto it = functions.begin(); it != functions.end(); it++)
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

    interface.append(it->toString());
  }

  return interface;
}
