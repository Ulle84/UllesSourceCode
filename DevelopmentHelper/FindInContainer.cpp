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

void FindInContainer::createCode()
{
  QString code = QString("auto %3 = std::find(%1.begin(), %1.end(), %2);\n\nif (%3 != %1.end())\n{\n  // element was found\n}\nelse\n{\n  // element was not found\n}").arg(ui->lineEditContainer->text()).arg(ui->lineEditElement->text()).arg(ui->lineEditIterator->text());
  QApplication::clipboard()->setText(code);
}
