#ifndef OPTIONSTEMPLATE_H
#define OPTIONSTEMPLATE_H

#include <QString>
#include <QStringList>

class OptionsTemplate
{
public:
  OptionsTemplate();

  QStringList m_files;
  QString m_folderInput;
  QString m_folderOutput;
  QString m_searchString;
  QString m_replaceString;
};

#endif // OPTIONSTEMPLATE_H
