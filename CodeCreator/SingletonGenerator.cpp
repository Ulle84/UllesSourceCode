#include "SingletonGenerator.h"
#include "ui_SingletonGenerator.h"

#include "CodeSaver.h"
#include "CodeGenerator.h"

SingletonGenerator::SingletonGenerator(CodeSaver* codeSaver, CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SingletonGenerator),
  m_codeSaver(codeSaver),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

SingletonGenerator::~SingletonGenerator()
{
  delete ui;
}
