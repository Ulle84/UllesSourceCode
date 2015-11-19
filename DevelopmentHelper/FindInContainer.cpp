#include <QClipboard>

#include "FindInContainer.h"
#include "ui_FindInContainer.h"

FindInContainer::FindInContainer(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::FindInContainer)
{
  ui->setupUi(this);
}

FindInContainer::~FindInContainer()
{
  delete ui;
}

void FindInContainer::on_lineEditContainer_returnPressed()
{
  createCode();
}

void FindInContainer::on_lineEditElement_returnPressed()
{
  createCode();
}

void FindInContainer::on_lineEditIterator_returnPressed()
{
  createCode();
}

void FindInContainer::on_checkBoxCreateElseBranch_stateChanged(int arg1)
{
  createCode();
}

void FindInContainer::createCode()
{
  QString iterator = ui->lineEditIterator->text();
  QString container = ui->lineEditContainer->text();
  QString element = ui->lineEditElement->text();

  QString findStatement = QString("std::find(%1.begin(), %1.end(), %2)").arg(container).arg(element);

  QString code;

  if (ui->lineEditIterator->text().isEmpty())
  {
    iterator = findStatement;
  }
  else
  {
    code.append(QString("auto %1 = %2;\n\n").arg(iterator).arg(findStatement));
  }

  code.append(QString("if (%1 != %2.end())\n{\n  // element was found\n}").arg(iterator).arg(container));

  if (ui->checkBoxCreateElseBranch->isChecked())
  {
    code.append("\nelse\n{\n  // element was not found\n}");
  }

  QApplication::clipboard()->setText(code);
}
