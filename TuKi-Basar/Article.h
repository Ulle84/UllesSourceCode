#ifndef ARTICLE_H
#define ARTICLE_H

#include <QString>

class Article
{
  //friend class ArticleManager;

public:
  Article(unsigned int articleNumber, unsigned int sellerNumber, unsigned int soldOnPc, double prize, QString size, QString description, QString soldTime);

  unsigned int m_soldOnPc;
  unsigned int m_articleNumber;
  unsigned int m_sellerNumber;
  double m_prize;
  QString m_size;
  QString m_description;
  QString m_soldTime;

private:
  //TODO declare variables private again?
};

#endif // ARTICLE_H
