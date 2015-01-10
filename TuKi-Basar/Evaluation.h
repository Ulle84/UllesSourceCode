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
  explicit Evaluation(ArticleManager* articleManager, Settings* settings, QWidget *parent = 0);
  ~Evaluation();

  void doEvaluation();
  void saveOverview();
  void saveSoldArticles();

private slots:
  void on_pushButtonSaveOverview_clicked();
  void on_pushButtonSaveSoldArticles_clicked();
  void on_webViewOverview_loadFinished(bool loadFinished);
  void on_webViewSoldArticles_loadFinished(bool loadFinished);

private:
  void updateWebViews();
  QByteArray createHtmlCodeOverview();
  QByteArray createHtmlCodeSoldArticles();

  Ui::Evaluation *ui;
  ArticleManager* m_articleManager;
  Settings* m_settings;

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
