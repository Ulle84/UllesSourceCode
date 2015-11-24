#include <QMessageBox>

#include "Decorator.h"
#include "ui_Decorator.h"
#include "Options.h"
#include "CodeGenerator.h"
#include "XmlHelper.h"
#include "InterfaceHelper.h"

Decorator::Decorator(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Decorator),
  mCodeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

Decorator::~Decorator()
{
  delete ui;
}

bool Decorator::generate(const QString &folder)
{
  if (!ui->checkBoxComponent->isChecked() && !ui->checkBoxDecorator->isChecked() && !ui->checkBoxInterface->isChecked())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("No option is selected!"));
    messageBox.exec();
    return false;
  }

  if (ui->checkBoxDecorator->isChecked() && ui->lineEditDecorator->text().isEmpty())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("Please enter a decorator name!"));
    messageBox.exec();
    return false;
  }

  if (ui->checkBoxComponent->isChecked() && ui->lineEditComponent->text().isEmpty())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("Please enter a component name!"));
    messageBox.exec();
    return false;
  }

  Options options;
  options.folderOutput = folder;
  options.folderInput = "Decorator/";

  options.searchAndReplace["Decorator"] = ui->lineEditDecorator->text();
  options.searchAndReplace["Component"] = ui->lineEditComponent->text();

  options.searchAndReplace["//TODO Implementation Decorator"] = InterfaceHelper::createFunctionImplementations(ui->plainTextEditInterface, "Decorator");
  options.searchAndReplace["//TODO Implementation Component"] = InterfaceHelper::createFunctionImplementations(ui->plainTextEditInterface, "Component");
  options.searchAndReplace["  // TODO add functions here"] = InterfaceHelper::createVirtualFunctionDeclarations(ui->plainTextEditInterface);
  options.searchAndReplace["  // IComponent"] = "  // IComponent\n" + InterfaceHelper::createFunctionDeclarations(ui->plainTextEditInterface);

  if (ui->checkBoxComponent->isChecked())
  {
    options.files << "Component.h";
    options.files << "Component.cpp";
  }

  if (ui->checkBoxInterface->isChecked())
  {
    options.files << "IComponent.h";
  }

  if (ui->checkBoxDecorator->isChecked())
  {
    options.files << "Decorator.h";
    options.files << "Decorator.cpp";
  }

  return mCodeGenerator->copyFromTemplate(options);
}

void Decorator::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditDecorator);
    }
    else if (xml.name() == "Component")
    {
      XmlHelper::readXml(xml, ui->lineEditComponent);
    }
    else if (xml.name() == "Interface")
    {
      XmlHelper::readXml(xml, ui->plainTextEditInterface);
    }
    else if (xml.name() == "GenerateDecorator")
    {
      XmlHelper::readXml(xml, ui->checkBoxDecorator);
    }
    else if (xml.name() == "GenerateComponent")
    {
      XmlHelper::readXml(xml, ui->checkBoxComponent);
    }
    else if (xml.name() == "GenerateInterface")
    {
      XmlHelper::readXml(xml, ui->checkBoxInterface);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Decorator::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditDecorator);
  XmlHelper::writeXml(xml, "Component", ui->lineEditComponent);
  XmlHelper::writeXml(xml, "Interface", ui->plainTextEditInterface);
  XmlHelper::writeXml(xml, "GenerateDecorator", ui->checkBoxDecorator);
  XmlHelper::writeXml(xml, "GenerateComponent", ui->checkBoxComponent);
  XmlHelper::writeXml(xml, "GenerateInterface", ui->checkBoxInterface);
}
void Decorator::on_checkBoxDecorator_toggled(bool checked)
{
    ui->lineEditDecorator->setEnabled(checked);
}

void Decorator::on_checkBoxComponent_toggled(bool checked)
{
    ui->lineEditComponent->setEnabled(checked);
}

void Decorator::on_checkBoxInterface_toggled(bool checked)
{
    ui->plainTextEditInterface->setEnabled(checked);
}
