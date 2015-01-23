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

  Options::Type type;

  bool useInheritance;
  bool usePimpl;
  bool disableCopy;

  QString name;
  QString inheritanceType;
  QString baseClassName;
  QString folder;
  QString functions;
};

inline Options::Options()
  : useInheritance(false),
    usePimpl(false),
    disableCopy(false)
{
}

#endif // OPTIONS_H
