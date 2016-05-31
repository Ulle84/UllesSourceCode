#ifndef INTERFACE_H
#define INTERFACE_H

#include <QList>

#include "Method.h"

class Interface : public QList<Method> // TODO really inherit of QList<Method> ?
{
public:
  Interface();
  Interface(const QString& name, const QString& interface);

  QString name();
  void setName(const QString& name);

  QString toString();

private:
  QString m_name;

  friend class InterfaceGui;
};

#endif // INTERFACE_H
