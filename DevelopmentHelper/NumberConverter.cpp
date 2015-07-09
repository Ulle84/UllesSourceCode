#include "NumberConverter.h"
#include "ui_NumberConverter.h"

NumberConverter::NumberConverter(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::NumberConverter)
{
  ui->setupUi(this);
}

NumberConverter::~NumberConverter()
{
  delete ui;
}

void NumberConverter::on_lineEditDec_returnPressed()
{
  updateWidgets(ui->lineEditDec, 10);
}

void NumberConverter::on_lineEditHex_returnPressed()
{
  updateWidgets(ui->lineEditHex, 16);
}

void NumberConverter::on_lineEditOct_returnPressed()
{
  updateWidgets(ui->lineEditOct, 8);
}

void NumberConverter::on_lineEditBin_returnPressed()
{
  updateWidgets(ui->lineEditBin, 2);
}

void NumberConverter::updateWidgets(QLineEdit* source, int base)
{
  bool conversionOkay;
  int number = source->text().toInt(&conversionOkay, base);

  if (conversionOkay)
  {
    if (source != ui->lineEditBin)
    {
      ui->lineEditBin->setText(QString::number(number, 2));
    }

    if (source != ui->lineEditOct)
    {
      ui->lineEditOct->setText(QString::number(number, 8));
    }

    if (source != ui->lineEditDec)
    {
      ui->lineEditDec->setText(QString::number(number, 10));
    }

    if (source != ui->lineEditHex)
    {
      ui->lineEditHex->setText(QString::number(number, 16));
    }
  }
  else
  {
    if (source != ui->lineEditBin)
    {
      ui->lineEditBin->setText("error");
    }

    if (source != ui->lineEditOct)
    {
      ui->lineEditOct->setText("error");
    }

    if (source != ui->lineEditDec)
    {
      ui->lineEditDec->setText("error");
    }

    if (source != ui->lineEditHex)
    {
      ui->lineEditHex->setText("error");
    }
  }
}
