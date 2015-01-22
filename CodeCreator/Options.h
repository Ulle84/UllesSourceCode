#ifndef OPTIONS_H
#define OPTIONS_H

#include <QString>
#include <QStringList>

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
  bool m_interface;

  QString m_name;
  QString m_inheritanceType;
  QString m_baseClassName;
  QString m_folder;
  QString m_functions;
};

#endif // OPTIONS_H
