#include "DecoratorExample.h"
#include "ui_DecoratorExample.h"

DecoratorExample::DecoratorExample(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DecoratorExample)
{
  ui->setupUi(this);
}

DecoratorExample::~DecoratorExample()
{
  delete ui;
}
