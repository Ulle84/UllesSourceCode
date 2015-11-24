#include <QMessageBox>

#include "Data.h"
#include "ui_Data.h"
#include "XmlHelper.h"
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

bool Data::generate(const QString &folder)
{
  if (ui->lineEditName->text().isEmpty())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("Please enter a name!"));
    messageBox.exec();
    return false;
  }

  Options options;
  options.folderOutput = folder;

  if (ui->checkBoxConstructor->isChecked())
  {
    options.folderInput = "Data/inlineConstructor/";
  }
  else
  {
    options.folderInput = "Data/base/";
  }

  options.files << "Data.h";

  options.searchAndReplace["Data"] = ui->lineEditName->text();
  // TODO set all options

  return mCodeGenerator->copyFromTemplate(options);
}

void Data::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    else if (xml.name() == "InlineConstructor")
    {
      XmlHelper::readXml(xml, ui->checkBoxConstructor);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Data::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  XmlHelper::writeXml(xml, "InlineConstructor", ui->checkBoxConstructor);
}
