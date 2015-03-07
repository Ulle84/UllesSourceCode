#ifndef TUKIBASAR_H
#define TUKIBASAR_H

#include <QMainWindow>

class Article;
class ArticleManager;
class Evaluation;
class Settings;
class SellerManager;

namespace Ui {
class TuKiBasar;
}

class TuKiBasar : public QMainWindow
{
  Q_OBJECT

public:
  explicit TuKiBasar(QWidget *parent = 0);
  ~TuKiBasar();

private slots:
  void on_actionSettings_triggered();
  void on_actionEvaluation_triggered();
  void on_actionImportArticleLists_triggered();
  void on_lineEditInput_returnPressed();
  void on_pushButtonDeleteLastInput_clicked();
  void on_pushButtonNextCustomer_clicked();
  void on_actionCompleteEvaluation_triggered();
  void on_pushButtonCorrectPrize_clicked();
  void on_actionExportSoldArticles_triggered();

  void on_pushButton_clicked(); //TODO remove after testing

  void on_doubleSpinBoxMoneyGiven_valueChanged(double moneyGiven);

  void on_actionSalesHistory_triggered();

  void on_pushButton_2_clicked();  //TODO remove after testing

  void on_actionActivateAdvancedAccess_triggered();

  void on_actionDeactivateAdvancedAccess_triggered();

private:
  void closeEvent(QCloseEvent *event);
  void setLastArticleInformation();
  void clearLastArticleInformation();
  void updateArticleView();
  void askUserToFinishCurrentSale();
  void prepareForNextInput();
  bool checkPassword();
  void calculateChange();

  Ui::TuKiBasar *ui;
  Settings* m_settings;
  Evaluation* m_evaluation;
  ArticleManager* m_articleManager;
  SellerManager* m_sellerManager;
};

#endif // TUKIBASAR_H
