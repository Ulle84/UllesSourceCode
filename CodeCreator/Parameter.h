#ifndef PARAMETER_H
#define PARAMETER_H

#include <QString>

class Parameter
{
public:
  Parameter(const QString& type, const QString& name, const QString& defaultValue = QString());
  Parameter(const QString& parameter);

  bool isValid() const;

  QString toString() const;

  QString type() const;
  QString name() const;
  QString defaultValue() const;

private:
  QString m_type;
  QString m_name;
  QString m_defaultValue;
};

#endif // PARAMETER_H
