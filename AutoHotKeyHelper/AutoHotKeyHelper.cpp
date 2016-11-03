#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "AutoHotKeyHelper.h"

AutoHotKeyHelper::AutoHotKeyHelper()
{

}

void AutoHotKeyHelper::appendToFile(const QString &fileName, const QString &wrong, const QString &correct)
{
  m_keys.clear();

  //:*:geschreiben::geschrieben

  QFile file(fileName);

  if (!file.exists())
  {
    return;
  }


  if (!file.open(QFile::ReadOnly | QFile::Text))
  {
    return;
  }

  QTextStream in(&file);
  QString fileContent = in.readAll();
  file.close();

  QStringList lines = fileContent.split('\n');

  for (auto it = lines.begin(); it != lines.end(); ++it)
  {
    if (it->startsWith(":*:"))
    {
      QString line = it->mid(3);
      QStringList splitted = line.split("::");

      if (splitted.length() == 2)
      {
        m_keys.append(splitted[0]);
      }
    }
  }

  if (!m_keys.contains(wrong))
  {
    lines.append(QString(":*:%1::%2").arg(wrong).arg(correct));
  }

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    return;
  }

  QTextStream out(&file);
  out << lines.join("\n");

  file.close();
}
