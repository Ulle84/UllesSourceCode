#include "Options.h"

Options::Options() :
  m_removeLineDelimiters(false),
  m_removeDoubleEmptyLines(true),
  m_removeEmptyLinesBeforeClosingBracket(true),
  m_removeEmptyLinesAfterOpeningBracket(true),
  m_removeUnnecessaryNamespaceStuff(false),
  m_removeUnnecessaryStuff(false),
  m_moveCommaToRightPlace(false)
{
}

void Options::enableAll()
{
  m_removeLineDelimiters = true;
  m_removeDoubleEmptyLines = true;
  m_removeEmptyLinesBeforeClosingBracket = true;
  m_removeEmptyLinesAfterOpeningBracket = true;
  m_removeUnnecessaryNamespaceStuff = true;
  m_removeUnnecessaryStuff = true;
  m_moveCommaToRightPlace = true;
}
