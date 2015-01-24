#include <QMessageBox>

#include "Class.h"
#include "ui_Class.h"

#include "Options.h"
#include "CodeGenerator.h"

Class::Class(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Class),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

Class::~Class()
{
  delete ui;
}

void Class::generate(const QString &folder)
{
  if (ui->checkBoxInherit->isChecked() && ui->comboBoxBaseClass->currentText().isEmpty())
  {
    QMessageBox mb;
    mb.setText(tr("Please enter a base name!"));
    mb.exec();
  }

  Options options;
  options.folderOutput = folder;

  options.files << "Template.cpp";
  options.files << "Template.h";

  if (ui->checkBoxUsePimpl->isChecked())
  {
    options.files << "TemplateImpl.h";
  }

  if (ui->checkBoxUsePimpl->isChecked())
  {
    if (ui->checkBoxDisableCopy->isChecked())
    {
      options.folderInput = "templates/Class/pImplNoCopy/";
    }
    else
    {
      options.folderInput = "templates/Class/pImpl/";
    }
  }
  else
  {
    if (ui->checkBoxDisableCopy->isChecked())
    {
      options.folderInput = "templates/Class/noCopy/";
    }
    else
    {
      options.folderInput = "templates/Class/base/";
    }
  }

  QString name = ui->lineEditName->text();
  QString baseClass = ui->comboBoxBaseClass->currentText();
  QString include;
  QString type = ui->comboBoxType->currentText();
  options.searchAndReplace["Template"] = name;
  if (ui->checkBoxInherit->isChecked())
  {
    if (baseClass.left(1) == "Q")
    {
      include = QString("<%1>").arg(baseClass);
    }
    else
    {
      include = QString("\"%1.h\"").arg(baseClass);
    }

    options.searchAndReplace[QString("class %1").arg(name)]
        = QString("#include %1\n\nclass %2 : %3 %5").arg(include).arg(name).arg(type).arg(baseClass);
  }

  m_codeGenerator->copyFromTemplate(options);
}

void Class::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      ui->lineEditName->setText(xml.readElementText());
    }
    else if (xml.name() == "DisableCopy")
    {
      ui->checkBoxDisableCopy->setChecked(xml.readElementText() == "true");
    }
    else if (xml.name() == "UsePimpl")
    {
      ui->checkBoxUsePimpl->setChecked(xml.readElementText() == "true");
    }
    else if (xml.name() == "Inherit")
    {
      ui->checkBoxInherit->setChecked(xml.readElementText() == "true");
    }
    else if (xml.name() == "Type")
    {
      ui->comboBoxType->setCurrentIndex(ui->comboBoxType->findText(xml.readElementText()));
    }
    else if (xml.name() == "BaseClasses")
    {
      QStringList options;
      while (xml.readNextStartElement())
      {
        if (xml.name() == "Option")
        {
          options.append(xml.readElementText());
        }
        else
        {
          xml.skipCurrentElement();
        }
      }
      ui->comboBoxBaseClass->addItems(options);
    }

    else if (xml.name() == "BaseClass")
    {
      ui->comboBoxBaseClass->setCurrentIndex(ui->comboBoxBaseClass->findText(xml.readElementText()));
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Class::writeXml(QXmlStreamWriter &xml)
{
  xml.writeTextElement("Name", ui->lineEditName->text());
  xml.writeTextElement("DisableCopy", ui->checkBoxDisableCopy->isChecked() ? "true" : "false");
  xml.writeTextElement("UsePimpl", ui->checkBoxUsePimpl->isChecked() ? "true" : "false");
  xml.writeTextElement("Inherit", ui->checkBoxInherit->isChecked() ? "true" : "false");
  xml.writeTextElement("Type", ui->comboBoxType->currentText());
  xml.writeStartElement("BaseClasses");
  for (int i = 0; i < ui->comboBoxBaseClass->count(); i++)
  {
    xml.writeTextElement("Option", ui->comboBoxBaseClass->itemText(i));
  }
  xml.writeEndElement(); // BaseClasses
  xml.writeTextElement("BaseClass", ui->comboBoxBaseClass->currentText());
}

void Class::on_checkBoxInherit_toggled(bool checked)
{
    ui->widgetInheritance->setEnabled(checked);
}

void Class::on_pushButtonClearHistory_clicked()
{
    ui->comboBoxBaseClass->clear();
}
