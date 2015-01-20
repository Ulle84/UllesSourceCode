#include "CodeSaver.h"

#include <QString>
#include <QStringList>
#include <QFile>

CodeSaver::CodeSaver()
{
}

bool CodeSaver::saveCode(const QString &fileName, const QStringList &content)
{
  QFile file(fileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    return false;
  }

  qint64 bytesWritten = file.write(content.join("\n").toStdString().c_str());

  file.close();

  return bytesWritten < 1 ? false : true;
}
