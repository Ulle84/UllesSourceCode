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
  options.folderOutput = folder;
  options.folderInput = "templates/CodeCreator/";

  options.searchAndReplace["CodeCreator"] = ui->lineEditName->text();
  //TODO set all options

  m_codeGenerator->copyFromTemplate(options);
}

void CodeCreator::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      ui->lineEditName->setText(xml.readElementText());
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void CodeCreator::writeXml(QXmlStreamWriter &xml)
{
  xml.writeTextElement("Name", ui->lineEditName->text());
}
