#include "Singleton.h"
#include "ui_Singleton.h"

#include "Options.h"
#include "CodeGenerator.h"

Singleton::Singleton(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Singleton),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

Singleton::~Singleton()
{
  delete ui;
}

void Singleton::generate(const QString &folder)
{
  Options options;
  options.folderOutput = folder;

  options.searchAndReplace["Singleton"] = ui->lineEditName->text();

  options.files << "Singleton.cpp";
  options.files << "Singleton.h";

  if (ui->comboBoxType->currentText() == "lazy")
  {
    options.folderInput = "templates/Singleton/lazy/";
  }
  else
  {
    options.folderInput = "templates/Singleton/eager/";
  }

  m_codeGenerator->copyFromTemplate(options);
}

void Singleton::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      ui->lineEditName->setText(xml.readElementText());
    }
    else if (xml.name() == "Type")
    {
      ui->comboBoxType->setCurrentIndex(ui->comboBoxType->findText(xml.readElementText()));
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Singleton::writeXml(QXmlStreamWriter &xml)
{
  xml.writeTextElement("Name", ui->lineEditName->text());
  xml.writeTextElement("Type", ui->comboBoxType->currentText());
}
