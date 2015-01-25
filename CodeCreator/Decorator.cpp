#include <QMessageBox>

#include "Decorator.h"
#include "ui_Decorator.h"
#include "Options.h"
#include "CodeGenerator.h"
#include "XmlHelper.h"

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
  options.folderInput = "templates/Decorator/";

  options.searchAndReplace["Decorator"] = ui->lineEditDecorator->text();
  options.searchAndReplace["Component"] = ui->lineEditComponent->text();
    
  options.files << "Decorator.h";
  options.files << "Decorator.cpp";
  // TODO verify all options

  return mCodeGenerator->copyFromTemplate(options);
}

void Decorator::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditDecorator);
      //ui->lineEditDecorator->setText(xml.readElementText());
    }
    else if (xml.name() == "Component")
    {
      XmlHelper::readXml(xml, ui->lineEditComponent);
      //ui->lineEditComponent->setText(xml.readElementText());
    }
    else if (xml.name() == "Interface")
    {
      QStringList lines;
      while (xml.readNextStartElement())
      {
        if (xml.name() == "Line")
        {
          lines.append(xml.readElementText());
        }
        else
        {
          xml.skipCurrentElement();
        }
      }
      ui->plainTextEditInterface->setPlainText(lines.join("\n"));
    }
    else if (xml.name() == "GenerateDecorator")
    {
      XmlHelper::readXml(xml, ui->checkBoxDecorator);
      //ui->checkBoxDecorator->setChecked(xml.readElementText() == "true");
    }
    else if (xml.name() == "GenerateComponent")
    {
      XmlHelper::readXml(xml, ui->checkBoxComponent);
      //ui->checkBoxComponent->setChecked(xml.readElementText() == "true");
    }
    else if (xml.name() == "GenerateInterface")
    {
      XmlHelper::readXml(xml, ui->checkBoxInterface);
      //ui->checkBoxInterface->setChecked(xml.readElementText() == "true");
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

  /*xml.writeTextElement("Name", ui->lineEditDecorator->text());
  xml.writeTextElement("Component", ui->lineEditComponent->text());
  xml.writeStartElement("Interface");
  QStringList lines = ui->plainTextEditInterface->toPlainText().split("\n");
  for (auto it = lines.begin(); it != lines.end(); it++)
  {
    xml.writeTextElement("Line", *it);
  }
  xml.writeEndElement(); // Interface
  xml.writeTextElement("GenerateDecorator", ui->checkBoxDecorator->isChecked() ? "true" : "false");
  xml.writeTextElement("GenerateComponent", ui->checkBoxComponent->isChecked() ? "true" : "false");
  xml.writeTextElement("GenerateInterface", ui->checkBoxInterface->isChecked() ? "true" : "false");*/
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
