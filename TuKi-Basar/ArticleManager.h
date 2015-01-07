#ifndef ARTICLEMANAGER_H
#define ARTICLEMANAGER_H

#include <QList>

#include "Article.h"

class ArticleManager
{
public:
  ArticleManager();
  ~ArticleManager();

  void addArticle(Article* article);
  void clear();
  Article* getArticle(int sellerNumber, int articleNumber);

  bool fromXml();
  bool toXml();

  void resetCurrentSale();
  void addArticleToCurrentSale(Article* article);
  void removeLastArticleFromCurrentSale();
  Article* getLastArticleInCurrentSale();
  QString currentSaleToText();
  QString currentSaleToHtml();
  QString prizeToString(double prize);

private:
  QList<Article*> m_articles;
  QList<Article*> m_currentSale;
  QString m_fileName;
};

#endif // ARTICLEMANAGER_H
