#ifndef OPTIONSTEMPLATE_H
#define OPTIONSTEMPLATE_H

#include <QMap>
#include <QString>
#include <QStringList>

class OptionsTemplate
{
public:
  QStringList files;
  QString folderInput;
  QString folderOutput;

  QMap<QString, QString> searchAndReplace;
};

#endif // OPTIONSTEMPLATE_H
