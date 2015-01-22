#include "CodeCreator.h"
#include "ui_CodeCreator.h"

#include "OptionsTemplate.h"
#include "CodeGenerator.h"

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
    OptionsTemplate options;
    options.m_folderOutput = folder;
    options.m_folderInput = "templates/CodeCreator/";
    //TODO set all options
    
    m_codeGenerator->copyFromTemplate(options);
}

void CodeCreator::readXml(QXmlStreamReader &xml)
{
}

void CodeCreator::writeXml(QXmlStreamWriter &xml)
{
}
