#include <QClipboard>
#include <QString>

#include "ConnectionHelper.h"
#include "ui_ConnectionHelper.h"

ConnectionHelper::ConnectionHelper(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ConnectionHelper)
{
  ui->setupUi(this);
}

ConnectionHelper::~ConnectionHelper()
{
  delete ui;
}

void ConnectionHelper::on_lineEditSender_returnPressed()
{
  createCode();
}

void ConnectionHelper::createCode()
{
  QString code = QString("connect(%1, SIGNAL(%2), %3, %4(%5));").arg(ui->lineEditSender->text()).arg(ui->comboBoxSignal->currentText()).arg(ui->lineEditReceiver->text()).arg(ui->comboBoxReceiverType->currentText()).arg(ui->comboBoxSlot->currentText());
  if (ui->checkBox->isChecked())
  {
    code.prepend("bool connected = ");
  }
  QApplication::clipboard()->setText(code);
}

void ConnectionHelper::on_checkBox_stateChanged(int arg1)
{
  createCode();
}

void ConnectionHelper::on_comboBoxReceiverType_currentIndexChanged(int index)
{
  createCode();
}

void ConnectionHelper::on_comboBoxSignal_currentTextChanged(const QString &arg1)
{
  createCode();
}

void ConnectionHelper::on_lineEditReceiver_returnPressed()
{
  createCode();
}

void ConnectionHelper::on_comboBoxSlot_currentTextChanged(const QString &arg1)
{
  createCode();
}
