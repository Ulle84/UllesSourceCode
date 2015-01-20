#ifndef HEADEROPTIONS_H
#define HEADEROPTIONS_H

#include <QString>

class HeaderOptions
{
public:
  HeaderOptions();

  QString m_className;

  bool m_useInheritance;
  QString m_inheritanceType;
  QString m_baseClassName;
};

#endif // HEADEROPTIONS_H
