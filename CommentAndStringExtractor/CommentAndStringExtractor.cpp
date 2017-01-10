#include <QDebug>

#include "CommentAndStringExtractor.h"

CommentAndStringExtractor::CommentAndStringExtractor()
{

}

void CommentAndStringExtractor::process(QString &code)
{
  ParseState parseState = ParseState::Normal;

  int startIndex = 0;

  QString test = "// horst";

  for (int i = 0; i < code.length(); ++i)
  {
    if (parseState == ParseState::Normal)
    {
      if (code[i] == '"' && peekPrevious(code, i) != QChar('\\'))
      {
        startIndex = i;
        parseState = ParseState::InsideString;
        continue;
      }
      // else test for comment etc
    }
    else if (parseState == ParseState::InsideString)
    {
      if (code[i] == '"' && peekPrevious(code, i) != QChar('\\'))
      {
        m_strings.append(code.mid(startIndex + 1, i - startIndex - 1));
        code.remove(startIndex + 1, i - startIndex - 1);
        parseState = ParseState::Normal;
        continue;
      }
    }
    else if (parseState == ParseState::InsideLineComment)
    {
      // TODO
    }
    else if (parseState == ParseState::InsideBlockComment)
    {
      // TODO
    }

  }
}

void CommentAndStringExtractor::revert(QString &code)
{

}

QChar CommentAndStringExtractor::peekPrevious(const QString &code, int index)
{
  if (index <= 0)
  {
    return QChar('\0');
  }

  return code[index - 1];
}

QChar CommentAndStringExtractor::peekNext(const QString &code, int index)
{
  if (index >= code.length())
  {
    return QChar('\0');
  }

  return code[index + 1];
}
