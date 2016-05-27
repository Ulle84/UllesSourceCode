#include <QDebug>
#include <QMessageBox>

#include "GeneratorInterface.h"
#include "ui_GeneratorInterface.h"
#include "Options.h"
#include "CodeGenerator.h"
#include "XmlHelper.h"
#include "InterfaceHelper.h"
#include "Class.h"
#include "Interface.h"
#include "Method.h"

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
  //QString interface = InterfaceHelper::createVirtualFunctionDeclarations(ui->plainTextEditFunctions);

  QString name = ui->lineEditName->text();
  if (ui->checkBoxPostfix->isChecked())
  {
    if (!name.endsWith("I"))
    {
      name.append("I");
    }
  }

  Class c(name);
  c.setConstructorDeclarationType(Class::DeclarationType::NoDeclaration);
  c.setDestructorDeclarationType(Class::DeclarationType::NoDeclaration);
  c.setMethods(Interface(name, ui->plainTextEditFunctions->toPlainText()));
  c.setOutputDirectory("D:\\ube\\Misc\\UllesSourceCode\\CodeCreator\\"); // TODO take folder of UI
  c.setOverwriteExistingFiles(true);

  c.createHeaderFile();

  return true;

  /*Options options;
  options.folderOutput = folder;
  options.folderInput = "Interface/";
  options.files << "Interface.h";
  options.searchAndReplace.append(qMakePair(QString("Interface"), name));
  options.searchAndReplace.append(qMakePair(QString("  // TODO add functions here"), interface));

  options.sortSearchAndReplaceList();

  return m_codeGenerator->copyFromTemplate(options);*/
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
      XmlHelper::readXml(xml, ui->checkBoxPostfix);
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
  XmlHelper::writeXml(xml, "Prefix", ui->checkBoxPostfix);
  XmlHelper::writeXml(xml, "Functions", ui->plainTextEditFunctions);
}
