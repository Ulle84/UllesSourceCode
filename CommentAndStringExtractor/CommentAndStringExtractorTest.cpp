#include <QString>
#include <QtTest>

#include "CommentAndStringExtractor.h"

class CommentAndStringExtractorTest : public QObject
{
  Q_OBJECT

public:
  CommentAndStringExtractorTest();

private Q_SLOTS:
  void lineComments();
  void lineCommentLeadingStar();
  void blockComment();
  void string();
  void notAString();
};

/*
  these two functions must be implemented, if required:
  void initTestCase();
  void cleanupTestCase();
*/

CommentAndStringExtractorTest::CommentAndStringExtractorTest()
{
}

void CommentAndStringExtractorTest::lineComments()
{
  QString code = "//test001\n//test002 \"not a string\"";
  CommentAndStringExtractor commentAndStringExtractor;
  commentAndStringExtractor.process(code);

  QCOMPARE(code, QString("//\n//"));

  QStringList expectedLineComments;
  expectedLineComments << "test001";
  expectedLineComments << "test002 \"not a string\"";

  QCOMPARE(commentAndStringExtractor.m_lineComments, expectedLineComments);
}

void CommentAndStringExtractorTest::lineCommentLeadingStar()
{
  QString code = "//*test002";
  CommentAndStringExtractor commentAndStringExtractor;
  commentAndStringExtractor.process(code);

  QCOMPARE(code, QString("//"));

  QStringList expectedLineComments;
  expectedLineComments << "*test002";

  QCOMPARE(commentAndStringExtractor.m_lineComments, expectedLineComments);
}

void CommentAndStringExtractorTest::blockComment()
{
  QString code = "/*test003*/";
  CommentAndStringExtractor commentAndStringExtractor;
  commentAndStringExtractor.process(code);

  QCOMPARE(code, QString("/**/"));

  QStringList expectedBlockComments;
  expectedBlockComments << "test003";

  QCOMPARE(commentAndStringExtractor.m_blockComments, expectedBlockComments);
}

void CommentAndStringExtractorTest::string()
{
  QString code = "test = \"// 004\"";
  CommentAndStringExtractor commentAndStringExtractor;
  commentAndStringExtractor.process(code);

  QCOMPARE(code, QString("test = \"\""));

  QStringList expectedStrings;
  expectedStrings << "// 004";

  QCOMPARE(commentAndStringExtractor.m_strings, expectedStrings);
}

void CommentAndStringExtractorTest::notAString()
{
  QString code = "char a = \'\\\"\'\nchar b = \'\\\"\'";
  CommentAndStringExtractor commentAndStringExtractor;
  commentAndStringExtractor.process(code);

  QCOMPARE(code, QString("char a = \'\\\"\'\nchar b = \'\\\"\'"));

  QStringList expectedStrings;

  QCOMPARE(commentAndStringExtractor.m_strings, expectedStrings);
}

QTEST_APPLESS_MAIN(CommentAndStringExtractorTest)

#include "CommentAndStringExtractorTest.moc"
