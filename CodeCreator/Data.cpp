#include <QMessageBox>

#include "Data.h"
#include "ui_Data.h"

#include "Options.h"
#include "CodeGenerator.h"

Data::Data(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Data),
  mCodeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

Data::~Data()
{
  delete ui;
}

void Data::generate(const QString &folder)
{
  if (ui->lineEditName->text().isEmpty())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("Please enter a name!"));
    messageBox.exec();
    return;
  }

  Options options;
  options.folderOutput = folder;

  if (ui->checkBoxConstructor->isChecked())
  {
    options.folderInput = "templates/Data/inlineConstructor/";
  }
  else
  {
    options.folderInput = "templates/Data/base/";
  }

  options.files << "Data.h";

  options.searchAndReplace["Data"] = ui->lineEditName->text();
  // TODO set all options

  mCodeGenerator->copyFromTemplate(options);
}

void Data::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      ui->lineEditName->setText(xml.readElementText());
    }
    else if (xml.name() == "InlineConstructor")
    {
      ui->checkBoxConstructor->setChecked(xml.readElementText() == "true");
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Data::writeXml(QXmlStreamWriter &xml)
{
  xml.writeTextElement("Name", ui->lineEditName->text());
  xml.writeTextElement("InlineConstructor", ui->checkBoxConstructor->isChecked() ? "true" : "false");
}
