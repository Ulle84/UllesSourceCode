#include <QClipboard>

#include "IterateOverContainer.h"
#include "ui_IterateOverContainer.h"

IterateOverContainer::IterateOverContainer(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::IterateOverContainer)
{
  ui->setupUi(this);
}

IterateOverContainer::~IterateOverContainer()
{
  delete ui;
}

void IterateOverContainer::on_lineEditContainerName_returnPressed()
{
  createCode();
}

void IterateOverContainer::on_lineEditIteratorName_returnPressed()
{
  createCode();
}

void IterateOverContainer::createCode()
{
  QString code = QString("for (auto %2 = %1.begin(); %2 != %1.end(); %2++)\n{\n\n}").arg(ui->lineEditContainerName->text()).arg(ui->lineEditIteratorName->text());
  QApplication::clipboard()->setText(code);
}
