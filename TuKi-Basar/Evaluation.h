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

private:
  Ui::Evaluation *ui;
  ArticleManager* m_articleManager;
};

#endif // EVALUATION_H
