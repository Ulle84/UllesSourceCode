#include <QDebug>

#include "CommentAndStringExtractor.h"

CommentAndStringExtractor::CommentAndStringExtractor()
{

}

void CommentAndStringExtractor::process(QString &code)
{
  ParseState parseState = ParseState::Normal;

  int startIndex = 0;

  for (int i = 0; i < code.length(); ++i)
  {
    if (parseState == ParseState::Normal)
    {
      if (code[i] == '"' && peekPrevious(code, i) != '\\')
      {
        startIndex = i + 1;
        parseState = ParseState::InsideString;
        continue;
      }
      else if (code[i] == '/')
      {
        if (peekNext(code, i) == '/')
        {
          startIndex = i + 2;
          parseState = ParseState::InsideLineComment;
          i++;
          continue;
        }
        else if (peekNext(code, i) == '*')
        {
          startIndex = i + 2;
          parseState = ParseState::InsideBlockComment;
          i++;
          continue;
        }
      }
      // TODO sanitize code if possible
    }
    else if (parseState == ParseState::InsideString)
    {
      if (code[i] == '"' && peekPrevious(code, i) != '\\')
      {
        m_strings.append(code.mid(startIndex, i - startIndex));
        code.remove(startIndex, i - startIndex);
        parseState = ParseState::Normal;
        continue;
      }
    }
    else if (parseState == ParseState::InsideLineComment)
    {
      // TODO check if content of line comment is neseccary
      if (code[i] == '\n')
      {
        m_lineComments.append(code.mid(startIndex, i - startIndex));
        code.remove(startIndex, i - startIndex);
        parseState = ParseState::Normal;
        continue;
      }
      else if (i == code.length() - 1)
      {
        m_lineComments.append(code.mid(startIndex, i - startIndex + 1));
        code.remove(startIndex, i - startIndex + 1);
        parseState = ParseState::Normal;
        continue;
      }
    }
    else if (parseState == ParseState::InsideBlockComment)
    {
      // TODO check if content of block comment is neseccary
      if (code[i] == '*' && peekNext(code, i) == '/')
      {
        m_blockComments.append(code.mid(startIndex, i - startIndex));
        code.remove(startIndex, i - startIndex);
        parseState = ParseState::Normal;
        i++;
        continue;
      }
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

QString CommentAndStringExtractor::parseNextWord(const QString &code, int &index)
{
  // TODO
}

QString CommentAndStringExtractor::parsePreviousWord(const QString &code, int &index)
{
  // TODO
}
