#include "PathSelector.h"
#include "ui_PathSelector.h"

PathSelector::PathSelector(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::PathSelector)
{
  ui->setupUi(this);
}

PathSelector::~PathSelector()
{
  delete ui;
}

void PathSelector::setLabelText(const QString &text)
{
  ui->label->setText(text);
}

void PathSelector::setButtonText(const QString &text)
{
  ui->pushButton->setText(text);
}
