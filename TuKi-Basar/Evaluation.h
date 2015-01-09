#ifndef EVALUATION_H
#define EVALUATION_H

#include <QDialog>

class ArticleManager;
class Settings;

namespace Ui {
class Evaluation;
}

class Evaluation : public QDialog
{
  Q_OBJECT

public:
  explicit Evaluation(ArticleManager* articleManager, QWidget *parent = 0);
  ~Evaluation();

  void doEvaluation();
  void setPrintButtonVisible(bool visible);
  void printEvaluation();

private slots:
  void on_pushButtonPrintEvaluation_clicked();
  void on_webView_loadFinished(bool loadFinished);

private:
  void updateWebView();
  QByteArray createHtmlCode();

  Ui::Evaluation *ui;
  ArticleManager* m_articleManager;

  double m_volumeOfSale;
  double m_deduction;
  double m_deductionPercentage;
  int m_countOfSales;
  int m_countOfSoldArticles;
  double m_articlesPerSale;
  int m_countOfAllArticles;
  double m_percentageOfSoldArticles;

  QString m_volumeOfSaleString;
  QString m_deductionString;
  QString m_deductionDisplayString;
  QString m_countOfSalesString;
  QString m_countOfSoldArticlesString;
  QString m_articlesPerSaleString;
  QString m_countOfAllArticlesString;
  QString m_percentageOfSoldArticlesString;
};

#endif // EVALUATION_H
