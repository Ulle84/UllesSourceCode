#ifndef PARAMETER_H
#define PARAMETER_H

#include <QString>

class Parameter
{
public:
  Parameter(const QString& type, const QString& name, const QString& defaultValue = QString());
  Parameter(const QString& parameter);
  Parameter();

  bool isValid() const;

  QString toString(bool suppressDefaultValue = false) const;

  QString type() const;
  void setType(const QString& type);

  QString name() const;
  void setName(const QString& name);

  QString defaultValue() const;
  void setDefaultValue(const QString& defaultValue);

private:
  QString m_type;
  QString m_name;
  QString m_defaultValue;

  friend class ParameterGui;
};

#endif // PARAMETER_H
