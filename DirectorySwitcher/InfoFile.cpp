#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QString>

#include "InfoFile.h"

InfoFile::InfoFile() :
  m_id(QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss"))
{
}

InfoFile::InfoFile(const QString& path) :
  m_id(QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")),
  m_path(path)
{
  readFromFile();
}

QString InfoFile::path()
{
  return m_path;
}

void InfoFile::setPath(const QString& path)
{
  m_path = path;
}

QString InfoFile::id()
{
  return m_id;
}

void InfoFile::setId(const QString& id)
{
  m_id = id;
}

QString InfoFile::content()
{
  return m_content;
}

void InfoFile::setContent(const QString& content)
{
  m_content = content;
}

bool InfoFile::writeToFile()
{
  QFile file(m_path);

  if (!file.open(QIODevice::WriteOnly))
  {
    qDebug() << QString("file %1 could not be opened").arg(m_path);
    return false;
  }

  QTextStream out(&file);

  out << "# " << m_id << "\n";

  out << m_content;

  file.close();

  return true;
}

bool InfoFile::readFromFile()
{
  QFile file(m_path);

  if (!file.exists())
  {
    qDebug() << QString("file %1 does not exist").arg(m_path);
    return false;
  }

  if (!file.open(QIODevice::ReadOnly))
  {
    qDebug() << QString("file %1 could not be opened").arg(m_path);
    return false;
  }

  QTextStream in(&file);

  QStringList fileContent = in.readAll().split('\n');

  if (fileContent.size() < 1)
  {
    qDebug() << QString("no header found");
    return false;
  }

  QString firstLine = fileContent.first();

  if (!firstLine.startsWith("# "))
  {
    qDebug() << QString("no ID found");
    return false;
  }

  m_id = firstLine.mid(2);

  fileContent.removeFirst();

  if (fileContent.size() > 0)
  {
    m_content = fileContent.join('\n');
  }

  file.close();
  return true;
}
