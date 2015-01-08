#include "Evaluation.h"
#include "ui_Evaluation.h"

#include "ArticleManager.h"
#include "Settings.h"

Evaluation::Evaluation(ArticleManager* articleManager, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Evaluation),
  m_articleManager(articleManager)
{
  ui->setupUi(this);
}

Evaluation::~Evaluation()
{
  delete ui;
}

void Evaluation::doEvaluation()
{
  double volumeOfSale;
  double deduction;
  double deductionPercentage;
  int countOfSales;
  int countOfSoldArticles;
  double articlesPerSale;

  m_articleManager->calculateStatistics(&volumeOfSale, &deduction, &deductionPercentage, &countOfSales, &countOfSoldArticles, &articlesPerSale);

  ui->labelVolumeOfSale->setText(QString("%1 Euro").arg(QString::number(volumeOfSale, 'f', 2).replace('.', ',')));
  ui->labelDeduction->setText(QString("%1 Euro").arg(QString::number(deduction, 'f', 2).replace('.', ',')));
  ui->labelDecuctionDisplay->setText(tr("Einbehalt (%1 Prozent des Umsatzes)").arg(deductionPercentage));
  ui->labelCountOfSales->setText(QString("%1").arg(countOfSales));
  ui->labelCountOfSoldArticles->setText(QString("%1").arg(countOfSoldArticles));
  ui->labelArticlesPerSale->setText(QString::number(articlesPerSale, 'f', 1).replace('.', ','));
}
