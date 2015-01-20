#include "InterfaceGenerator.h"
#include "ui_InterfaceGenerator.h"

InterfaceGenerator::InterfaceGenerator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::InterfaceGenerator)
{
  ui->setupUi(this);
}

InterfaceGenerator::~InterfaceGenerator()
{
  delete ui;
}
