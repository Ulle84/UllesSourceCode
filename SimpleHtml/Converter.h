#ifndef CONVERTER_H
#define CONVERTER_H

#include <QString>

#include "Attribute.h"

class Converter
{
public:
  Converter();

  QString toHtml(const QString& simpleHtml);

private:
  enum class ParserState
  {

  };

  QString indent(int indentationLevel);
  QString parseTag(const QString& simpleHtml, int position);
  Attribute parseAttribute(const QString& simpleHtml, int& position);
  QString endTag(const QString& startTag);

  const int m_indent = 2;
};

#endif // CONVERTER_H
