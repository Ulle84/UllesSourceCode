#include "SingletonGenerator.h"
#include "ui_SingletonGenerator.h"

#include "CodeGenerator.h"

SingletonGenerator::SingletonGenerator(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SingletonGenerator),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

SingletonGenerator::~SingletonGenerator()
{
  delete ui;
}
