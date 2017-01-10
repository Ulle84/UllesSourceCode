#ifndef COMMENTANDSTRINGEXTRACTOR_H
#define COMMENTANDSTRINGEXTRACTOR_H

#include <QString>
#include <QStringList>

class CommentAndStringExtractor
{
public:
  CommentAndStringExtractor();
  void process(QString& code);
  void revert(QString& code);

private:
  QChar peekPrevious(const QString& code, int index);
  QChar peekNext(const QString& code, int index);

  enum class ParseState
  {
    Normal,
    InsideLineComment,
    InsideBlockComment,
    InsideString
  };

  QStringList m_lineComments;
  QStringList m_blockComments;
  QStringList m_strings;

  friend class CommentAndStringExtractorTest;
};

#endif
