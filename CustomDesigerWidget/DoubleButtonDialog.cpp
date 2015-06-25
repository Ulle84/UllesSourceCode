#include "DoubleButtonDialog.h"
#include "ui_DoubleButtonDialog.h"

#include "DoubleButton.h"

DoubleButtonDialog::DoubleButtonDialog(DoubleButton* doubleButton, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::DoubleButtonDialog)
{
  ui->setupUi(this);

  m_doubleButton = doubleButton;

  ui->lineEditTextButton1->setText(doubleButton->buttonText1());
  ui->lineEditTextButton2->setText(doubleButton->buttonText2());
}

DoubleButtonDialog::~DoubleButtonDialog()
{
  delete ui;
}

QString DoubleButtonDialog::buttonText1()
{
  return ui->lineEditTextButton1->text();
}

QString DoubleButtonDialog::buttonText2()
{
  return ui->lineEditTextButton2->text();
}

void DoubleButtonDialog::setButtonText1(const QString &buttonText1)
{
  ui->lineEditTextButton1->setText(buttonText1);
}

void DoubleButtonDialog::setButtonText2(const QString &buttonText2)
{
  ui->lineEditTextButton2->setText(buttonText2);
}
