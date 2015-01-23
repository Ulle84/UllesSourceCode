#ifndef OPTIONS_H
#define OPTIONS_H

#include <QMap>
#include <QString>
#include <QStringList>

class Options
{
public:
  QStringList files;
  QString folderInput;
  QString folderOutput;

  QMap<QString, QString> searchAndReplace;
};

#endif // OPTIONS_H
