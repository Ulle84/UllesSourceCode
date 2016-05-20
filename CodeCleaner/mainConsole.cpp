#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>

#include "CodeCleaner.h"

int main(int argc, char* argv[])
{
  for (int i = 1; i < argc; i++)
  {
    QFile file(argv[i]);

    if (!file.exists())
    {
      qDebug() << "file does not exist:" << argv[i];
      continue;
    }

    qDebug() << "processing file:" << argv[i];

    if (!file.open(QFile::ReadWrite | QFile::Text))
    {
      qDebug() << "can not open file:" << argv[i];
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

    file.close();
  }

  return 0;
}
