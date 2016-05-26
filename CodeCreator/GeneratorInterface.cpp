#include <QMessageBox>

#include "GeneratorInterface.h"
#include "ui_GeneratorInterface.h"
#include "Options.h"
#include "CodeGenerator.h"
#include "XmlHelper.h"
#include "InterfaceHelper.h"

GeneratorInterface::GeneratorInterface(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorInterface),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

GeneratorInterface::~GeneratorInterface()
{
  delete ui;
}

bool GeneratorInterface::generate(const QString &folder)
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

void GeneratorInterface::readXml(QXmlStreamReader &xml)
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

void GeneratorInterface::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  XmlHelper::writeXml(xml, "Prefix", ui->checkBoxPrefix);
  XmlHelper::writeXml(xml, "Functions", ui->plainTextEditFunctions);
}
