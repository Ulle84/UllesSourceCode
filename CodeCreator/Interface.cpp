#include "Interface.h"

#include <QSTringList>

Interface::Interface()
  : m_toImplement(true)
{
}

Interface::Interface(const QString &name, const QString &interface)
  : m_toImplement(true),
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

QString Interface::name() const
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

bool Interface::isToImplement() const
{
  return m_toImplement;
}

void Interface::setToImplement(bool toImplement)
{
  m_toImplement = toImplement;
}

bool Interface::hasPublicMethods() const
{
  return hasDeclarationType(Method::DeclarationType::Public);
}

QList<Method> Interface::publicMethods() const
{
  return methods(Method::DeclarationType::Public);
}

bool Interface::hasProtectedMethods() const
{
  return hasDeclarationType(Method::DeclarationType::Protected);
}

QList<Method> Interface::protectedMethods() const
{
  return methods(Method::DeclarationType::Protected);
}

bool Interface::hasPrivateMethods() const
{
  return hasDeclarationType(Method::DeclarationType::Private);
}

QList<Method> Interface::privateMethods() const
{
  return methods(Method::DeclarationType::Private);
}

void Interface::setAllMethodsPublicPureVirtual()
{
  for (auto it = begin(); it != end(); it++)
  {
    it->setDeclarationType(Method::DeclarationType::Public);
    it->setType(Method::Type::PureVirtual);
  }
}

bool Interface::hasDeclarationType(Method::DeclarationType declarationType) const
{
  for (auto it = begin(); it != end(); it++)
  {
    if (it->declarationType() == declarationType)
    {
      return true;
    }
  }

  return false;
}

QList<Method> Interface::methods(Method::DeclarationType declarationType) const
{
  QList<Method> methods;

  for (auto it = begin(); it != end(); it++)
  {
    if (it->declarationType() == declarationType)
    {
      methods.append(*it);
    }
  }

  return methods;
}
