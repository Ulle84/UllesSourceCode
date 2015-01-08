#ifndef TUKIBASAR_H
#define TUKIBASAR_H

#include <QMainWindow>

class Article;
class ArticleManager;
class Evaluation;
class Settings;

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

private:
  void setLastArticleInformation(Article* article);
  void clearLastArticleInformation();
  void updateArticleView();
  void askUserToFinishCurrentSale();

  Ui::TuKiBasar *ui;
  Settings* m_settings;
  Evaluation* m_evaluation;
  ArticleManager* m_articleManager;
};

#endif // TUKIBASAR_H
