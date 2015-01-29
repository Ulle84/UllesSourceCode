#include "CodeHelper.h"
#include "ui_CodeHelper.h"
#include <QApplication>
#include <QClipboard>

CodeHelper::CodeHelper(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CodeHelper)
{
  ui->setupUi(this);
}

CodeHelper::~CodeHelper()
{
  delete ui;
}

void CodeHelper::on_lineEditContainer_editingFinished()
{
  QString code = QString("for (auto it = %1.begin(); it != %1.end(); it++)\n{\n\n}\n").arg(ui->lineEditContainer->text());
  QApplication::clipboard()->setText(code);
}
