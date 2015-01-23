#include "Class.h"
#include "ui_Class.h"

#include "Options.h"
#include "CodeGenerator.h"

Class::Class(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Class),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

Class::~Class()
{
  delete ui;
}

void Class::generate(const QString &folder)
{
  Options options;
  options.folderOutput = folder;

  options.files << "Template.cpp";
  options.files << "Template.h";

  if (ui->checkBoxUsePimpl->isChecked())
  {
    options.files << "TemplateImpl.h";
  }

  if (ui->checkBoxUsePimpl->isChecked())
  {
    if (ui->checkBoxDisableCopy->isChecked())
    {
      options.folderInput = "templates/Class/pImplNoCopy/";
    }
    else
    {
      options.folderInput = "templates/Class/pImpl/";
    }
  }
  else
  {
    if (ui->checkBoxDisableCopy->isChecked())
    {
      options.folderInput = "templates/Class/noCopy/";
    }
    else
    {
      options.folderInput = "templates/Class/base/";
    }
  }

  options.searchAndReplace["Template"] = ui->lineEditName->text();

  m_codeGenerator->copyFromTemplate(options);
}

void Class::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      ui->lineEditName->setText(xml.readElementText());
    }
    else if (xml.name() == "DisableCopy")
    {
      ui->checkBoxDisableCopy->setChecked(xml.readElementText() == "true");
    }
    else if (xml.name() == "UsePimpl")
    {
      ui->checkBoxUsePimpl->setChecked(xml.readElementText() == "true");
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Class::writeXml(QXmlStreamWriter &xml)
{
  xml.writeTextElement("Name", ui->lineEditName->text());
  xml.writeTextElement("DisableCopy", ui->checkBoxDisableCopy->isChecked() ? "true" : "false");
  xml.writeTextElement("UsePimpl", ui->checkBoxUsePimpl->isChecked() ? "true" : "false");
}
