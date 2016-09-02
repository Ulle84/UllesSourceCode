#include <iostream>

#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QProcess>

#include "CodeCleaner.h"
#include "Options.h"

int main(int argc, char* argv[])
{
  Options options;

  for (int i = 1; i < argc; i++)
  {
    QString argument = argv[i];

    if (argument == "-r")
    {
      //rigorousMode
      std::cout << "CodeCleaner: switching on rigorousMode" << std::endl;
      options.enableAll();

      continue;
    }

    QString fileName(argument);

    std::cout << "CodeCleaner: working on file: " << fileName.toStdString() << std::endl;

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
      std::cout << "CodeCleaner: file has unallowed extension" << std::endl;
      continue;
    }

    QFile file(fileName);

    if (!file.exists())
    {
      std::cout << "CodeCleaner: file does not exist" << std::endl;
      continue;
    }

    std::cout << "CodeCleaner: calling AStyle" << std::endl;

    QStringList aStyleArguments;

    if (fileName.endsWith(".cpp"))
    {
      aStyleArguments << "--options=AStyleOptionsCpp.txt";
    }
    else if (fileName.endsWith(".hpp"))
    {
      aStyleArguments << "--options=AStyleOptionsH.txt";
    }
    else if (fileName.endsWith(".h"))
    {
      aStyleArguments << "--options=AStyleOptionsH.txt";
    }

    aStyleArguments << fileName;

    QProcess::execute("AStyle.exe", aStyleArguments);

    if (!file.open(QFile::ReadWrite | QFile::Text))
    {
      std::cout << "CodeCleaner: can not open file" << std::endl;
      continue;
    }

    QTextStream textStream(&file);

    QString fileContent = textStream.readAll();

    CodeCleaner codeCleaner(fileContent);
    codeCleaner.setOptions(options);
    codeCleaner.process();
    QString modifiedContent = codeCleaner.getCode();

    if (fileContent != modifiedContent)
    {
      file.resize(0); // clears the file
      textStream << modifiedContent;
      std::cout << "CodeCleaner: file modified" << std::endl;
    }
    else
    {
      std::cout << "CodeCleaner: file is unchanged" << std::endl;
    }

    file.close();
  }

  return 0;
}
