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
  bool m_singleton;

  QString m_className;
  QString m_inheritanceType;
  QString m_baseClassName;
  QString m_folder;
};

#endif // OPTIONS_H
