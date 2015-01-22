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

void InterfaceGenerator::generate(const QString &folder)
{
  Options options;
  options.m_type = Options::Interface;
  options.m_folder = folder;
  options.m_name = ui->lineEditName->text();
  options.m_interface = true;
  options.m_functions = ui->plainTextEditFunctions->toPlainText();

  m_codeGenerator->generateCode(options);
}

void InterfaceGenerator::readXml(QXmlStreamReader &xml)
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

void InterfaceGenerator::writeXml(QXmlStreamWriter &xml)
{
  xml.writeTextElement("Name", ui->lineEditName->text());
}
