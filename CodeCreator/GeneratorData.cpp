#include "GeneratorData.h"
#include "ui_GeneratorData.h"

GeneratorData::GeneratorData(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorData)
{
  ui->setupUi(this);
}

GeneratorData::~GeneratorData()
{
  delete ui;
}
