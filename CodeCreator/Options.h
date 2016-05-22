#ifndef OPTIONS_H
#define OPTIONS_H

#include <QMap>
#include <QList>
#include <QPair>
#include <QString>
#include <QStringList>

class Options
{
public:
  Options();

  void sortSearchAndReplaceList();

  QStringList files;
  QString folderInput;
  QString folderOutput;
  QList<QPair<QString, QString> > searchAndReplace;
};

#endif // OPTIONS_H
