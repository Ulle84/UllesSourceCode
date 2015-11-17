#include <QClipboard>

#include "ForLoopCreator.h"
#include "ui_ForLoopCreator.h"

ForLoopCreator::ForLoopCreator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ForLoopCreator)
{
  ui->setupUi(this);
}

ForLoopCreator::~ForLoopCreator()
{
  delete ui;
}

void ForLoopCreator::on_lineEditForLoopIterator_returnPressed()
{
  createCode();
}

void ForLoopCreator::on_lineEditForLoopEnd_returnPressed()
{
  createCode();
}

void ForLoopCreator::createCode()
{
  QString code = QString("for (int %1 = 0; i < %2; %1++)\n{\n\n}").arg(ui->lineEditForLoopIterator->text()).arg(ui->lineEditForLoopEnd->text());
  QApplication::clipboard()->setText(code);
}
