#ifndef OPTIONS_H
#define OPTIONS_H

#include <QString>

class Options
{
public:
  Options();

  enum Type
  {
    Class,
    Interface,
    Singleton
  };

  Options::Type m_type;

  bool m_useInheritance;
  bool m_usePimpl;
  bool m_disableCopy;

  QString m_className;
  QString m_inheritanceType;
  QString m_baseClassName;
};

#endif // OPTIONS_H
