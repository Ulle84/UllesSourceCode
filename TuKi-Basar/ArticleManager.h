#ifndef ARTICLEMANAGER_H
#define ARTICLEMANAGER_H

#include <map>

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
  bool isArticleInCurrentSale(unsigned int sellerNumber, unsigned int articleNumber);
  Article* getLastArticleInCurrentSale();
  QString currentSaleToText();
  QString currentSaleToHtml();
  QString prizeToString(double prize);

  void calculateStatistics(double* volumeOfSale, double* deduction, double* deductionPercentage, int* countOfSales, int* countOfSoldArticles, double* articlesPerSale, int* countOfAllArticles, double* percentageOfSoldArticles);
  std::map<int, double> getSellerMatrix();
  std::map<int, double> getArticleMatrix(int sellerNumber);
  void sync(ArticleManager* other);

  double getPayOutFactor();

private:
  QList<Article*> m_articles;
  QList<Article*> m_currentSale;
  QString m_fileName;
  Settings* m_settings;
};

#endif // ARTICLEMANAGER_H
