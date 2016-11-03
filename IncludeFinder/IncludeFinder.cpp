#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>

#include "IncludeFinder.h"

IncludeFinder::IncludeFinder()
{
  m_extensions << ".cpp";
  m_extensions << ".hpp";
  m_extensions << ".h";
}

QStringList IncludeFinder::files(const QString &directory, const QStringList &includes)
{
  QStringList result;

  QDirIterator dirIterator(directory, QDirIterator::Subdirectories);

  while (dirIterator.hasNext())
  {
    QString fileName = dirIterator.next();

    for (auto it = m_extensions.begin(); it != m_extensions.end(); ++it)
    {
      if (fileName.endsWith(*it))
      {
        QFile file(fileName);


        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
          continue;
        }

        QTextStream in(&file);
        QString fileContent = in.readAll();
        file.close();

        // TODO delete comments
        // TODO shared code?

        QStringList lines = fileContent.split('\n');

        for (auto it2 = lines.begin(); it2 != lines.end(); ++it2)
        {
          QString trimmed = it2->trimmed();
          if (trimmed.startsWith("#include"))
          {
            for (auto it3 = includes.begin(); it3 != includes.end(); ++it3)
            {
              if (trimmed.contains(*it3))
              {
                result << fileName;
                continue;
              }
            }
          }
        }
      }
    }
  }

  return result;
}
