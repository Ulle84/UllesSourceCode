#include "PrizeCorrection.h"
#include "ui_PrizeCorrection.h"

PrizeCorrection::PrizeCorrection(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::PrizeCorrection)
{
  ui->setupUi(this);
}

PrizeCorrection::~PrizeCorrection()
{
  delete ui;
}

void PrizeCorrection::setPrize(double prize)
{
  ui->doubleSpinBoxPrize->setValue(prize);
  ui->doubleSpinBoxPrize->selectAll();
}

double PrizeCorrection::getPrize()
{
  return ui->doubleSpinBoxPrize->value();
}
