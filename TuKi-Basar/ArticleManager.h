#ifndef ARTICLEMANAGER_H
#define ARTICLEMANAGER_H

#include <QList>

#include "Article.h"

class Settings;

class ArticleManager
{
public:
  ArticleManager(Settings* settings, QString fileName);
  ~ArticleManager();

  void addArticle(Article* article);
  void clear();
  Article* getArticle(int sellerNumber, int articleNumber);

  bool fromXml();
  bool toXml();

  void resetCurrentSale();
  void addArticleToCurrentSale(Article* article);
  void removeLastArticleFromCurrentSale();
  void finishCurrentSale(unsigned int pcNumber);
  bool isCurrentSaleEmpty();
  Article* getLastArticleInCurrentSale();
  QString currentSaleToText();
  QString currentSaleToHtml();
  QString prizeToString(double prize);

  void calculateStatistics(double* volumeOfSale, double* deduction, double* deductionPercentage, int* countOfSales, int* countOfSoldArticles, double* articlesPerSale);

private:
  QList<Article*> m_articles;
  QList<Article*> m_currentSale;
  QString m_fileName;
  Settings* m_settings;
};

#endif // ARTICLEMANAGER_H
