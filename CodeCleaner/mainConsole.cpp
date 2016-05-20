#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>

#include "CodeCleaner.h"

int main(int argc, char* argv[])
{
  for (int i = 1; i < argc; i++)
  {
    QString fileName(argv[i]);

    QStringList allowedExtensions;
    allowedExtensions << ".cpp" << ".hpp" << ".h";

    bool hasAllowedExtension = false;

    for (auto it = allowedExtensions.begin(); it != allowedExtensions.end(); it++)
    {
      if (fileName.endsWith(*it))
      {
        hasAllowedExtension = true;
        break;
      }
    }

    if (!hasAllowedExtension)
    {
      qDebug() << "file has unallowed extension:" << fileName;
      continue;
    }

    QFile file(fileName);

    if (!file.exists())
    {
      qDebug() << "file does not exist:" << fileName;
      continue;
    }

    qDebug() << "processing file:" << fileName;

    if (!file.open(QFile::ReadWrite | QFile::Text))
    {
      qDebug() << "can not open file:" << fileName;
      continue;
    }

    QTextStream textStream(&file);

    QString fileContent = textStream.readAll();

    CodeCleaner codeCleaner(fileContent);
    codeCleaner.process();
    QString modifiedContent = codeCleaner.getCode();

    if (fileContent != modifiedContent)
    {
      file.resize(0); // clears the file
      textStream << modifiedContent;
    }
    else
    {
      qDebug() << "file is unchanged";
    }

    file.close();
  }

  return 0;
}
