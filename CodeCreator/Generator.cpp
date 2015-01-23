#include <QDir>
#include <QFile>
#include <QStringList>
#include <QTextStream>

#include "CodeGenerator.h"
#include "Options.h"
#include "Generator.h"
#include "ui_Generator.h"

Generator::Generator(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Generator),
  mCodeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

Generator::~Generator()
{
  delete ui;
}

void Generator::generate(const QString &folder)
{
  Options options;
  options.folderOutput = folder;
  options.folderInput = "templates/CodeCreator/";

  options.files << "CodeCreator.h";
  options.files << "CodeCreator.cpp";
  options.files << "CodeCreator.ui";

  options.searchAndReplace["CodeCreator"] = ui->lineEditName->text();

  mCodeGenerator->copyFromTemplate(options);
}

void Generator::readXml(QXmlStreamReader &xml)
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

void Generator::writeXml(QXmlStreamWriter &xml)
{
  xml.writeTextElement("Name", ui->lineEditName->text());
}
