#include "SingletonGenerator.h"
#include "ui_SingletonGenerator.h"

SingletonGenerator::SingletonGenerator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SingletonGenerator)
{
  ui->setupUi(this);
}

SingletonGenerator::~SingletonGenerator()
{
  delete ui;
}
