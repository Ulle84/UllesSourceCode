#include <QMessageBox>

#include "CodeCreator.h"
#include "ui_CodeCreator.h"

#include "Options.h"
#include "CodeGenerator.h"

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

void CodeCreator::generate(const QString &folder)
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
  options.folderInput = "templates/CodeCreator/";

  options.searchAndReplace["CodeCreator"] = ui->lineEditName->text();
    
  options.files << "CodeCreator.h";
  options.files << "CodeCreator.cpp";
  // TODO verify all options

  mCodeGenerator->copyFromTemplate(options);
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
