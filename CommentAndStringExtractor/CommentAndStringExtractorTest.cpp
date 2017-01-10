#include <QString>
#include <QtTest>

#include "CommentAndStringExtractor.h"

class CommentAndStringExtractorTest : public QObject
{
  Q_OBJECT

public:
  CommentAndStringExtractorTest();

private Q_SLOTS:
  void test001();
  void test002();
  void test003();
  void test004();
};

/*
  these two functions must be implemented, if required:
  void initTestCase();
  void cleanupTestCase();
*/

CommentAndStringExtractorTest::CommentAndStringExtractorTest()
{
}

void CommentAndStringExtractorTest::test001()
{
  QString code = "//test001";
  CommentAndStringExtractor commentAndStringExtractor;
  commentAndStringExtractor.process(code);

  QCOMPARE(code, QString("//"));

  QStringList expectedLineComments;
  expectedLineComments << "test001";

  QCOMPARE(commentAndStringExtractor.m_lineComments, expectedLineComments);
}

void CommentAndStringExtractorTest::test002()
{
  QString code = "//*test002";
  CommentAndStringExtractor commentAndStringExtractor;
  commentAndStringExtractor.process(code);

  QCOMPARE(code, QString("//"));

  QStringList expectedLineComments;
  expectedLineComments << "*test002";

  QCOMPARE(commentAndStringExtractor.m_lineComments, expectedLineComments);
}

void CommentAndStringExtractorTest::test003()
{
  QString code = "/*test003*/";
  CommentAndStringExtractor commentAndStringExtractor;
  commentAndStringExtractor.process(code);

  QCOMPARE(code, QString("/**/"));

  QStringList expectedBlockComments;
  expectedBlockComments << "test003";

  QCOMPARE(commentAndStringExtractor.m_blockComments, expectedBlockComments);
}

void CommentAndStringExtractorTest::test004()
{
  QString code = "test = \"// 004\"";
  CommentAndStringExtractor commentAndStringExtractor;
  commentAndStringExtractor.process(code);

  QCOMPARE(code, QString("test = \"\""));

  QStringList expectedStrings;
  expectedStrings << "// 004";

  QCOMPARE(commentAndStringExtractor.m_strings, expectedStrings);
}

QTEST_APPLESS_MAIN(CommentAndStringExtractorTest)

#include "CommentAndStringExtractorTest.moc"
