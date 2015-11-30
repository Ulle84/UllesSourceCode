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

void ConnectionHelper::on_lineEditSignal_returnPressed()
{
  createCode();
}

void ConnectionHelper::on_lineEditReceiver_returnPressed()
{
  createCode();
}

void ConnectionHelper::on_lineEditSlot_returnPressed()
{
  createCode();
}

void ConnectionHelper::createCode()
{
  QString code = QString("connect(%1, SIGNAL(%2), %3, SLOT(%4));").arg(ui->lineEditSender->text()).arg(ui->lineEditSignal->text()).arg(ui->lineEditReceiver->text()).arg(ui->lineEditSlot->text());
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
