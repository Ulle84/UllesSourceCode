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

void SingletonGenerator::generate(const QString &folder)
{
  // TODO check parameters

  Options options;
  options.m_type = Options::Singleton;
  options.m_folder = folder;

  // TODO further options

  m_codeGenerator->generateCode(options);
}

void SingletonGenerator::readXml(QXmlStreamReader &xml)
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

void SingletonGenerator::writeXml(QXmlStreamWriter &xml)
{
  xml.writeTextElement("Name", ui->lineEditName->text());
}
