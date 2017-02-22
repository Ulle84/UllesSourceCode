#ifndef CPPHIGHLIGHTER_H
#define CPPHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class QTextDocument;

class CppHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    CppHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override;

private:
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
};

#endif
