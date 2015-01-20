#include "CodeCreator.h"
#include "ui_CodeCreator.h"

#include "ClassGenerator.h"

CodeCreator::CodeCreator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CodeCreator)
{
  ui->setupUi(this);

  m_classGenerator = new ClassGenerator(this);

  ui->generators->layout()->addWidget(m_classGenerator);
}

CodeCreator::~CodeCreator()
{
  delete ui;
}
