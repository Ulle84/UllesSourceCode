#ifndef INTERFACE_H
#define INTERFACE_H

#include <QList>

#include "Function.h"

class Interface : public QList<Function>
{
public:
  Interface();
  Interface(const QString& interface);

  void setName(const QString& name);

  QString toString();

private:
  QString m_name;
};

#endif // INTERFACE_H
