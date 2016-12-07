#include "TimerDoneDialog.h"
#include "ui_TimerDoneDialog.h"

TimerDoneDialog::TimerDoneDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::TimerDoneDialog)
{
  ui->setupUi(this);
}

TimerDoneDialog::~TimerDoneDialog()
{
  delete ui;
}
