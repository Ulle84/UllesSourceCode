#ifndef OPTIONS_H
#define OPTIONS_H

#include <QMap>
#include <QString>
#include <QStringList>

class Options
{
public:
  Options();

  QStringList files;
  QString folderInput;
  QString folderOutput;

  QMap<QString, QString> searchAndReplace;
};

inline Options::Options()
  : folderInput("false")
{
}

#endif // OPTIONS_H
