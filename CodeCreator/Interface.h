#ifndef INTERFACE_H
#define INTERFACE_H

#include <QList>

#include "Method.h"

class Interface : public QList<Method>
{
public:
  Interface();
  Interface(const QString& name, const QString& interface);

  QString name();
  void setName(const QString& name);

  QString toString();

private:
  QString m_name;
};

#endif // INTERFACE_H
