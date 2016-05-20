#include <QDebug>

#include "CodeCleaner.h"

CodeCleaner::CodeCleaner(QString string) :
  m_string(string)
{
}

void CodeCleaner::process()
{
  removeDoubleEmptyLines();
  removeEmptyLinesBeforeClosingBracket();
  removeEmptyLinesAfterOpeningBracket();
  removeLineDelimiters();
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
  m_string.replace("\n  //-----------------------------------------------------------------------------\n", "\n");
  m_string.replace("\n  /****************************************************************************/\n", "\n");

  //m_string.replace("\n      //////////////////////////////////////////////////////////////////////////\n      else ", "\n      else ");
}

QString CodeCleaner::createSpaceString(unsigned int length)
{
  QString string;
  for (unsigned int i = 0; i < length; i++)
  {
    string.append(' ');
  }
  return string;
}

QString CodeCleaner::getCode()
{
  return m_string;
}
