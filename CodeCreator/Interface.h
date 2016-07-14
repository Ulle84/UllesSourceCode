#ifndef INTERFACE_H
#define INTERFACE_H

#include <QList>

#include "Method.h"

class Interface : public QList<Method>
{
public:
  Interface();
  Interface(const QString& name, const QString& interface);

  QString name() const;
  void setName(const QString& name);

  QString toString();

  bool isToImplement() const;
  void setToImplement(bool toImplement);

  bool hasPublicMethods() const;
  QList<Method> publicMethods() const;

  bool hasProtectedMethods() const;
  QList<Method> protectedMethods() const;

  bool hasPrivateMethods() const;
  QList<Method> privateMethods() const;

  void setAllMethodsPublicPureVirtual();

private:
  bool hasDeclarationType(Method::DeclarationType declarationType) const;
  QList<Method> methods(Method::DeclarationType declarationType) const;

  QString m_name;
  bool m_toImplement;

  friend class InterfaceGui;
};

#endif // INTERFACE_H
