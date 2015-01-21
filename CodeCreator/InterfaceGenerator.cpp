#include "InterfaceGenerator.h"
#include "ui_InterfaceGenerator.h"

#include "CodeGenerator.h"
#include "Options.h"

InterfaceGenerator::InterfaceGenerator(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::InterfaceGenerator),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

InterfaceGenerator::~InterfaceGenerator()
{
  delete ui;
}

void InterfaceGenerator::on_pushButtonStart_clicked()
{
  Options options;
  options.m_type = Options::Interface;
}
