#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextStream>

#include "CodeCleaner.h"

int main(int argc, char *argv[])
{

  for (int i = 1; i < argc; i++)
  {
    qDebug() << "processing file:" << argv[i];

    QFile file(argv[i]);
    if (!file.open(QFile::ReadWrite | QFile::Text)) continue;
    QTextStream textStream(&file);


    QString fileContent = textStream.readAll();

    CodeCleaner codeCleaner(fileContent);
    codeCleaner.process();

    file.resize(0); // clears the file

    textStream << codeCleaner.getCode();


    file.close();
  }



  return 0;
}
