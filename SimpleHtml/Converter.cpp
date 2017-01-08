#include <QStringList>
#include <QDebug>

#include "Converter.h"

Converter::Converter()
{

}

QString Converter::toHtml(const QString &simpleHtml)
{
  QString input = removeComments(simpleHtml);

  QString string = "<html>\n<head>\n</head>\n<body>";

  QList<QString> tags;

  QChar c;
  bool lastCharWasOpeningBracket = false;

  for (int i = 0; i < input.size(); ++i)
  {
    c = input[i];

    if (c == '(')
    {
      if (lastCharWasOpeningBracket)
      {
        Attribute attribute = parseAttribute(input, i);
        if (attribute.isValid())
        {
          string.insert(string.length() - 1, QString(" %1=\"%2\"").arg(attribute.name()).arg(attribute.value()));
        }
        else
        {
          tags.append(QString());
        }
      }
      else
      {
        QString tag = parseTag(input, i);

        tags.append(tag);

        if (!tag.isEmpty())
        {
          string.remove(string.length() - tag.length(), tag.length());
          string.append(QString("<%1>").arg(tag));
        }
      }
    }
    else if (c == ')')
    {
      QString tag = tags.last();
      tags.removeLast();
      if (!tag.isEmpty())
      {
        if (lastCharWasOpeningBracket)
        {
          string.insert(string.length() - 1, '/');
        }
        else
        {
          string.append(QString("</%1>").arg(tag));
        }
      }
    }
    else
    {
      string.append(c);
    }

    lastCharWasOpeningBracket = (c == '(');
  }

  string.append("\n</body>\n</html>");

  return string;
}

QString Converter::removeComments(const QString &simpleHtml)
{
  // TODO nested comments?
  // this part here might be easy, but what about the code-highlighting?

  QString string = simpleHtml;

  int beginIndex = string.indexOf(m_beginComment);
  int endIndex = -1;

  while (beginIndex >= 0)
  {
    endIndex = string.indexOf(m_endComment, beginIndex + m_beginComment.length());

    if (endIndex >= 0)
    {
      string.remove(beginIndex, endIndex - beginIndex + m_endComment.length());
    }

    beginIndex = string.indexOf(m_beginComment, beginIndex + 1);
  }

  return string;
}

/*QString Converter::indent(int indentationLevel)
{
  return QString(indentationLevel * m_indent, ' ');
}*/

QString Converter::parseTag(const QString &simpleHtml, int position)
{
  if (position <= 0)
  {
    return QString();
  }

  int originalPosition = position;

  QChar c;

  bool runLoop = true;

  while (runLoop)
  {
    c = simpleHtml[--position];

    if (c == ' ' || c == '(' || c == ')' || c == '\n' || c == '\t')
    {
      ++position;
      runLoop = false;
    }

    if (position == 0)
    {
      runLoop = false;
    }
  }

  return simpleHtml.mid(position, originalPosition - position);
}

Attribute Converter::parseAttribute(const QString &simpleHtml, int &position)
{
  int originalPosition = position;

  QChar c;

  bool runLoop = true;

  while (runLoop)
  {
    c = simpleHtml[++position];

    if (c == ')')
    {
      runLoop = false;
    }

    if (position == simpleHtml.size() - 1)
    {
      // reached end of string to early
      position = originalPosition;
      return Attribute();
    }
  }

  QString attribute = simpleHtml.mid(originalPosition + 1, position - originalPosition - 1);

  QStringList tokens = attribute.split('=');

  if (tokens.size() != 2)
  {
    position = originalPosition;
    return Attribute();
  }

  QString name = tokens[0].trimmed();
  QString value = tokens[1].trimmed();

  if (name.isEmpty() || value.isEmpty())
  {
    position = originalPosition;
    return Attribute();
  }

  return Attribute(name, value);
}

/*QString Converter::endTag(const QString &startTag)
{
  if (startTag.isEmpty())
  {
    return startTag;
  }

  QString string = startTag;

  string.insert(startTag.length() - 2, '/');
  return string;
}*/
