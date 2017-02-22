#ifndef SIMPLEHTMLHIGHLIGHTER_H
#define SIMPLEHTMLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class QTextDocument;

class SimpleHtmlHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT

public:
  SimpleHtmlHighlighter(QTextDocument* parent = 0);

protected:
  void highlightBlock(const QString &text) override;

private:
  void init();

  struct HighlightingRule
  {
    QRegExp pattern;
    QTextCharFormat format;
  };

  QVector<HighlightingRule> highlightingRules;

  QRegExp commentStartExpression;
  QRegExp commentEndExpression;

  QTextCharFormat keywordFormat;
  QTextCharFormat classFormat;
  QTextCharFormat singleLineCommentFormat;
  QTextCharFormat multiLineCommentFormat;
  QTextCharFormat quotationFormat;
  QTextCharFormat functionFormat;
  QTextCharFormat parameterFormat;
  QTextCharFormat headerFormat;
};

#endif
