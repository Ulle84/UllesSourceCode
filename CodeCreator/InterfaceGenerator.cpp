#include "InterfaceGenerator.h"
#include "ui_InterfaceGenerator.h"

#include "CodeSaver.h"
#include "CodeGenerator.h"

InterfaceGenerator::InterfaceGenerator(CodeSaver* codeSaver, CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::InterfaceGenerator),
  m_codeSaver(codeSaver),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

InterfaceGenerator::~InterfaceGenerator()
{
  delete ui;
}
