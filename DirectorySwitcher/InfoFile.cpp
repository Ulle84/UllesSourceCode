#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

#include "InfoFile.h"

InfoFile::InfoFile(const QString& path) :
  m_id(QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss"))
{
  QFile file(path);

  if (!file.exists())
  {
    qDebug() << QString("file %1 does not exist").arg(path);
    return;
  }

  if (!file.open(QIODevice::ReadOnly))
  {
    qDebug() << QString("file %1 could not be opened").arg(path);
    return;
  }

  QTextStream in(&file);

  QStringList fileContent = in.readAll().split('\n');

  if (fileContent.size() < 2)
  {
    qDebug() << QString("no header found");
    return;
  }

  QString firstLine = fileContent.first();

  if (!firstLine.startsWith("ID: "))
  {
    qDebug() << QString("no ID found");
    return;
  }

  m_id = firstLine.mid(4);

  fileContent.removeFirst();
  fileContent.removeFirst();

  if (fileContent.size() > 0)
  {
    m_content = fileContent.join('\n');
  }

  file.close();
}

QString InfoFile::id()
{
  return m_id;
}

QString InfoFile::content()
{
  return m_content;
}
