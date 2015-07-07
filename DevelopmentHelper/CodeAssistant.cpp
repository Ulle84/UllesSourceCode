#include <QClipboard>

#include "CodeAssistant.h"
#include "ui_CodeAssistant.h"

CodeAssistant::CodeAssistant(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CodeAssistant)
{
  ui->setupUi(this);
}

CodeAssistant::~CodeAssistant()
{
  delete ui;
}

void CodeAssistant::on_lineEditContainer_returnPressed()
{
  QString code = QString("for (auto it = %1.begin(); it != %1.end(); it++)\n{\n\n}\n").arg(ui->lineEditContainer->text());
  QApplication::clipboard()->setText(code);
}

void CodeAssistant::on_lineEditForLoop_returnPressed()
{
  QString code = QString("for (int i = 0; i < %1; i++)\n{\n\n}\n").arg(ui->lineEditForLoop->text());
  QApplication::clipboard()->setText(code);
}
