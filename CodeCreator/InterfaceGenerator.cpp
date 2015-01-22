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
  QString name = ui->lineEditName->text();

  if (ui->checkBoxPrefix->isChecked())
  {
    name.prepend("I");
  }

  if (ui->checkBoxPostfix->isChecked())
  {
    name.append("Interface");
  }

  Options options;
  options.m_type = Options::Interface;
  options.m_folder = folder;
  options.m_name = name;
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
    else if (xml.name() == "Prefix")
    {
      ui->checkBoxPrefix->setChecked(xml.readElementText() == "true");
    }
    else if (xml.name() == "Postfix")
    {
      ui->checkBoxPostfix->setChecked(xml.readElementText() == "true");
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
  xml.writeTextElement("Prefix", ui->checkBoxPrefix->isChecked() ? "true" : "false");
  xml.writeTextElement("Postfix", ui->checkBoxPostfix->isChecked() ? "true" : "false");
}

void InterfaceGenerator::on_checkBoxPrefix_toggled(bool checked)
{
    if (checked)
    {
      ui->checkBoxPostfix->setChecked(false);
    }
}

void InterfaceGenerator::on_checkBoxPostfix_toggled(bool checked)
{
  if (checked)
  {
    ui->checkBoxPrefix->setChecked(false);
  }
}
