#include <QMessageBox>

#include "ClassAdvanced.h"
#include "ui_ClassAdvanced.h"
#include "Options.h"
#include "CodeGenerator.h"
#include "XmlHelper.h"

ClassAdvanced::ClassAdvanced(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ClassAdvanced),
  mCodeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

ClassAdvanced::~ClassAdvanced()
{
  delete ui;
}

bool ClassAdvanced::generate(const QString &folder)
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
  options.folderInput = "ClassAdvanced/";

  options.searchAndReplace.append(qMakePair(QString("ClassAdvanced"), ui->lineEditName->text()));
    
  options.files << "ClassAdvanced.h";
  options.files << "ClassAdvanced.cpp";
  // TODO verify all options

  return mCodeGenerator->copyFromTemplate(options);
}

void ClassAdvanced::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    // TODO read further elements
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void ClassAdvanced::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  // TODO write further elements
}