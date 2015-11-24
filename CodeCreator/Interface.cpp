#include "Interface.h"
#include "ui_Interface.h"
#include "XmlHelper.h"
#include "Options.h"
#include "CodeGenerator.h"
#include "InterfaceHelper.h"

Interface::Interface(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Interface),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

Interface::~Interface()
{
  delete ui;
}

bool Interface::generate(const QString &folder)
{
  QString interface = InterfaceHelper::createVirtualFunctionDeclarations(ui->plainTextEditFunctions);

  QString name = ui->lineEditName->text();
  if (ui->checkBoxPrefix->isChecked())
  {
    name.prepend("I");
  }

  Options options;
  options.folderOutput = folder;
  options.folderInput = "Interface/";
  options.files << "Interface.h";
  options.searchAndReplace.append(qMakePair(QString("Interface"), name));
  options.searchAndReplace.append(qMakePair(QString("  // TODO add functions here"), interface));

  options.sortSearchAndReplaceList();

  return m_codeGenerator->copyFromTemplate(options);
}

void Interface::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    else if (xml.name() == "Functions")
    {
      XmlHelper::readXml(xml, ui->plainTextEditFunctions);
    }
    else if (xml.name() == "Prefix")
    {
      XmlHelper::readXml(xml, ui->checkBoxPrefix);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Interface::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  XmlHelper::writeXml(xml, "Prefix", ui->checkBoxPrefix);
  XmlHelper::writeXml(xml, "Functions", ui->plainTextEditFunctions);
}
