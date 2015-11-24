#include <QMessageBox>

#include "CodeCreator.h"
#include "ui_CodeCreator.h"
#include "Options.h"
#include "CodeGenerator.h"
#include "XmlHelper.h"

CodeCreator::CodeCreator(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CodeCreator),
  mCodeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

CodeCreator::~CodeCreator()
{
  delete ui;
}

bool CodeCreator::generate(const QString &folder)
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
  options.folderInput = "CodeCreator/";

  options.searchAndReplace.append(qMakePair(QString("CodeCreator"), ui->lineEditName->text()));
    
  options.files << "CodeCreator.h";
  options.files << "CodeCreator.cpp";
  // TODO verify all options

  return mCodeGenerator->copyFromTemplate(options);
}

void CodeCreator::readXml(QXmlStreamReader &xml)
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

void CodeCreator::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  // TODO write further elements
}
