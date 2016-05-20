#include <QDebug>
#include <QStringList>
#include <QVector>

#include "CodeCleaner.h"

CodeCleaner::CodeCleaner(QString string) :
  m_string(string)
{
}

void CodeCleaner::process()
{
  removeLineDelimiters();
  removeDoubleEmptyLines();
  removeEmptyLinesBeforeClosingBracket();
  removeEmptyLinesAfterOpeningBracket();
  removeUnnecessaryNamespaceStuff();
  removeUnnecessaryStuff();
  moveCommaToRightPlace();
}

void CodeCleaner::removeDoubleEmptyLines()
{
  while (m_string.contains("\n\n\n"))
  {
    m_string.replace("\n\n\n", "\n\n");
  }
}

void CodeCleaner::removeEmptyLinesBeforeClosingBracket()
{
  for (unsigned int indent = 0; indent < 20; indent++)
  {
    QString space = createSpaceString(indent * 2);
    QString search = "\n\n" + space + "}";
    QString replace = "\n" + space + "}";

    m_string.replace(search, replace);
  }
}

void CodeCleaner::removeEmptyLinesAfterOpeningBracket()
{
  m_string.replace("{\n\n", "{\n");
}

void CodeCleaner::removeLineDelimiters()
{
  QVector<QString> delimterChars;
  delimterChars.append("-");
  delimterChars.append(" -");
  delimterChars.append("=");
  delimterChars.append("*");
  delimterChars.append("~");

  for (auto delimiter = delimterChars.begin(); delimiter != delimterChars.end(); delimiter++)
  {
    for (unsigned int indent = 0; indent < 3; indent++)
    {
      QString space = createSpaceString(indent * 2);

      for (unsigned int i = 1; i < 120; i++)
      {
        QString delimiterString = createString(*delimiter, i);

        QString search = "\n" + space + "//" + delimiterString + "\n";
        m_string.replace(search, "\n");

        search = "\n" + space + "// " + delimiterString + "\n";
        m_string.replace(search, "\n");

        search = "\n" + space + "/*" + delimiterString + "*/\n";
        m_string.replace(search, "\n");
      }
    }
  }

  QStringList delimiters;
  delimiters.append("  //--   --   --   --   --   --   --   --   --   --   --   --   --   --   --   --   --");

  for (auto it = delimiters.begin(); it != delimiters.end(); it++)
  {
    m_string.replace("\n" + *it + "\n", "\n");
  }
}

void CodeCleaner::removeUnnecessaryNamespaceStuff()
{
  QStringList namespaces;
  namespaces << "Base";
  namespaces << "CU";
  namespaces << "Catalog";
  namespaces << "Comm";
  namespaces << "Core";
  namespaces << "Data";
  namespaces << "ExML";
  namespaces << "Exp";
  namespaces << "Gui";
  namespaces << "Instr";
  namespaces << "Main";
  namespaces << "Qt";
  namespaces << "Script";
  namespaces << "Store";
  namespaces << "View";

  QMap<QString, QString> replaceMap;

  for (int i = 0; i < 5; i++)
  {
    QString spaces = createSpaceString(i);
    replaceMap["}" + spaces + "//end of namespace\n"] = "}\n";
    replaceMap["}" + spaces + "// end of namespace\n"] = "}\n";

    for (auto it = namespaces.begin(); it != namespaces.end(); it++)
    {
      replaceMap["}" + spaces + "//namespace " + *it + "\n"] = "}\n";
      replaceMap["}" + spaces + "// namespace " + *it + "\n"] = "}\n";
    }
  }

  for (auto it = replaceMap.begin(); it != replaceMap.end(); it++)
  {
    m_string.replace(it.key(), it.value());
  }
}

void CodeCleaner::removeUnnecessaryStuff()
{
  QMap<QString, QString> replaceMap;

  replaceMap["  /*****************************************************************************\n      \\brief\n   ****************************************************************************/"] = "";
  replaceMap["  /*****************************************************************************\n     \\brief\n  ****************************************************************************/"] = "";
  replaceMap["  /*****************************************************************************\n\n   ****************************************************************************/"] = "";
  replaceMap["  /*******************************************************************************\n\n  ******************************************************************************/"] = "";
  replaceMap["  //////////////////////////////////////////////////////////////////////////////\n  //////////////////////////////////////////////////////////////////////////////\n  //////////////////////////////////////////////////////////////////////////////"] = "";
  replaceMap["  ////////////////////////////////////////////////////////////////////////////////\n  ////////////////////////////////////////////////////////////////////////////////\n  ////////////////////////////////////////////////////////////////////////////////\n  ////////////////////////////////////////////////////////////////////////////////\n  ////////////////////////////////////////////////////////////////////////////////"] = "";

  for (auto it = replaceMap.begin(); it != replaceMap.end(); it++)
  {
    m_string.replace(it.key(), it.value());
  }
}

void CodeCleaner::moveCommaToRightPlace()
{
  m_string.replace("\n    , ", ",\n      ");
}

QString CodeCleaner::createSpaceString(unsigned int length)
{
  return createString(" ", length);
}

QString CodeCleaner::createString(QString characters, unsigned int length)
{
  QString string;

  for (unsigned int i = 0; i < length; i++)
  {
    string.append(characters);
  }

  return string;
}

QString CodeCleaner::getCode()
{
  return m_string;
}
