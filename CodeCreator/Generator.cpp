#include <QDir>
#include <QFile>
#include <QStringList>
#include <QTextStream>

#include "CodeGenerator.h"
#include "Options.h"
#include "Generator.h"
#include "ui_Generator.h"
#include "XmlHelper.h"

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

bool Generator::generate(const QString &folder)
{
  Options options;
  options.folderOutput = folder;
  options.folderInput = "CodeCreator/";

  options.files << "CodeCreator.h";
  options.files << "CodeCreator.cpp";
  options.files << "CodeCreator.ui";

  options.searchAndReplace["CodeCreator"] = ui->lineEditName->text();

  return mCodeGenerator->copyFromTemplate(options);
}

void Generator::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Generator::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
}
