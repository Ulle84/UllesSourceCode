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

  QStringList files;
  QString folderInput;
  QString folderOutput;

  QMap<QString, QString> searchAndReplace; // TODO QList<QPair<QString, QString>> instead of QMap<QString, QString> -> sort this list in all existing templates to be reverse compatible -> use macro qMakePair
};

inline Options::Options()
  : folderInput("false")
{
}

#endif // OPTIONS_H
