#ifndef HEADEROPTIONS_H
#define HEADEROPTIONS_H

#include <QString>

class HeaderOptions
{
public:
  HeaderOptions();

  bool m_useInheritance;
  bool m_usePimpl;
  bool m_disableCopy;

  QString m_className;
  QString m_inheritanceType;
  QString m_baseClassName;
};

#endif // HEADEROPTIONS_H
