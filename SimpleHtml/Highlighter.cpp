#include <QDebug>

#include "Highlighter.h"
#include "QColorEx.h"

Highlighter::Highlighter(QTextDocument *parent) :
  QSyntaxHighlighter(parent)
{
  init();
}


void Highlighter::init()
{
  HighlightingRule rule;

  functionFormat.setForeground(Qt::blue);
  rule.pattern = QRegExp("\\b[A-Za-z0-9]+(?=\\()");
  rule.format = functionFormat;
  highlightingRules.append(rule);

  headerFormat.setForeground(QBrush(QColorEx::orange()));
  rule.pattern = QRegExp("\\bh[1-6]+(?=\\()");

  // TODO also mark the caption itself
  // attention: opneing and closing paranthesis must be countet
  // e.g. h1(hello world u(test) continue)
  // the hightlighting may not stop at the first closing parenthesis but must stop at second
  rule.format = headerFormat;
  highlightingRules.append(rule);

  keywordFormat.setForeground(Qt::darkBlue);
  keywordFormat.setFontWeight(QFont::Bold);
  QStringList keywordPatterns;
  keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                  << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                  << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                  << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                  << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                  << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                  << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                  << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                  << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                  << "\\bvoid\\b" << "\\bvolatile\\b";
  foreach (const QString &pattern, keywordPatterns)
  {
    rule.pattern = QRegExp(pattern);
    rule.format = keywordFormat;
    highlightingRules.append(rule);
  }

  classFormat.setFontWeight(QFont::Bold);
  classFormat.setForeground(Qt::darkMagenta);
  rule.pattern = QRegExp("\\bQ[A-Za-z]+\\b");
  rule.format = classFormat;
  highlightingRules.append(rule);

  /*singleLineCommentFormat.setForeground(Qt::red);
  rule.pattern = QRegExp("//[^\n]*");
  rule.format = singleLineCommentFormat;
  highlightingRules.append(rule);*/

  parameterFormat.setForeground(Qt::red);
  rule.pattern = QRegExp("\\([^()]+=[^()]+\\)");
  rule.format = parameterFormat;
  highlightingRules.append(rule);

  multiLineCommentFormat.setForeground(Qt::red);

  quotationFormat.setForeground(Qt::darkGreen);
  rule.pattern = QRegExp("\".*\"");
  rule.format = quotationFormat;
  highlightingRules.append(rule);

  commentStartExpression = QRegExp("/\\*");
  commentEndExpression = QRegExp("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
{
  //qDebug() << "------- hightligtBlock -------";
  //qDebug() << text;

  foreach (const HighlightingRule &rule, highlightingRules)
  {
    QRegExp expression(rule.pattern);
    int index = expression.indexIn(text);
    while (index >= 0)
    {
      int length = expression.matchedLength();
      setFormat(index, length, rule.format);
      index = expression.indexIn(text, index + length);
    }
  }

  /*setCurrentBlockState(0);

  int startIndex = 0;
  if (previousBlockState() != 1)
  {
    startIndex = commentStartExpression.indexIn(text);
  }

  while (startIndex >= 0)
  {
    int endIndex = commentEndExpression.indexIn(text, startIndex);
    int commentLength;
    if (endIndex == -1)
    {
      setCurrentBlockState(1);
      commentLength = text.length() - startIndex;
    }
    else
    {
      commentLength = endIndex - startIndex + commentEndExpression.matchedLength();
    }
    setFormat(startIndex, commentLength, multiLineCommentFormat);
    startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
  }*/
}
