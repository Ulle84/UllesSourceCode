#include "Converter.h"
#include "ui_Converter.h"

Converter::Converter(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Converter)
{
  ui->setupUi(this);
}

Converter::~Converter()
{
  delete ui;
}
