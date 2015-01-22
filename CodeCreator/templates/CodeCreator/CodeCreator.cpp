#include "CodeCreator.h"
#include "ui_CodeCreator.h"

CodeCreator::CodeCreator(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CodeCreator),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

CodeCreator::~CodeCreator()
{
  delete ui;
}

void CodeCreator::generate(const QString &folder)
{
}

void CodeCreator::readXml(QXmlStreamReader &xml)
{
}

void CodeCreator::writeXml(QXmlStreamWriter &xml)
{
}
