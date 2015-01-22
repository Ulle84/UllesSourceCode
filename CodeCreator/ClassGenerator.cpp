#include "ClassGenerator.h"
#include "ui_ClassGenerator.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>

#include "CodeGenerator.h"
#include "Options.h"

ClassGenerator::ClassGenerator(CodeGenerator* codeGenerator, QWidget* parent) :
  QWidget(parent),
  ui(new Ui::ClassGenerator),
  m_fileName("Settings.xml"),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

ClassGenerator::~ClassGenerator()
{
  delete ui;
}

void ClassGenerator::generate(const QString& folder)
{
  if (ui->lineEditName->text().isEmpty())
  {
    QMessageBox mb;
    mb.setText(tr("Class name is empty!"));
    mb.exec();
    return;
  }

  if (ui->checkBoxInherit->isChecked() && ui->comboBoxBaseClassName->currentText().isEmpty())
  {
    QMessageBox mb;
    mb.setText(tr("Base class name is empty!"));
    mb.exec();
    return;
  }

  Options options;
  options.m_type = Options::Class;
  options.m_useInheritance = ui->checkBoxInherit->isChecked();
  options.m_usePimpl = ui->checkBoxUsePimpl->isChecked();
  options.m_disableCopy = ui->checkBoxDisableCopy->isChecked();
  options.m_name = ui->lineEditName->text();
  options.m_inheritanceType = ui->comboBoxType->currentText();
  options.m_baseClassName = ui->comboBoxBaseClassName->currentText();
  options.m_folder = folder;

  m_codeGenerator->generateCode(options);
}

void ClassGenerator::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      ui->lineEditName->setText(xml.readElementText());
    }
    else if (xml.name() == "Inheritance")
    {
      while (xml.readNextStartElement())
      {
        if (xml.name() == "Inherit")
        {
          ui->checkBoxInherit->setChecked(xml.readElementText() == "true");
        }
        else if (xml.name() == "Type")
        {
          ui->comboBoxType->setCurrentIndex(ui->comboBoxType->findText(xml.readElementText()));
        }
        else if (xml.name() == "BaseClassNames")
        {
          while (xml.readNextStartElement())
          {
            if (xml.name() == "BaseClassName")
            {
              ui->comboBoxBaseClassName->addItem(xml.readElementText());
            }
            else
            {
              xml.skipCurrentElement();
            }
          }
        }
        else if (xml.name() == "SelectedBaseClassName")
        {
          ui->comboBoxBaseClassName->setCurrentIndex(ui->comboBoxBaseClassName->findText(xml.readElementText()));
        }
        else
        {
          xml.skipCurrentElement();
        }
      }
    }
    else if (xml.name() == "DisableCopy")
    {
      ui->checkBoxDisableCopy->setChecked(xml.readElementText() == "true");
    }
    else if (xml.name() == "UsePimpl")
    {
      ui->checkBoxUsePimpl->setChecked(xml.readElementText() == "true");
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void ClassGenerator::writeXml(QXmlStreamWriter &xml)
{
  xml.writeTextElement("Name", ui->lineEditName->text());
  xml.writeTextElement("DisableCopy", ui->checkBoxDisableCopy->isChecked() ? "true" : "false");
  xml.writeTextElement("UsePimpl", ui->checkBoxUsePimpl->isChecked() ? "true" : "false");

  xml.writeStartElement("Inheritance");
  xml.writeTextElement("Inherit", ui->checkBoxInherit->isChecked() ? "true" : "false");
  xml.writeTextElement("Type", ui->comboBoxType->currentText());
  xml.writeStartElement("BaseClassNames");

  for (int i = 0; i < ui->comboBoxBaseClassName->count(); i++)
  {
    xml.writeTextElement("BaseClassName", ui->comboBoxBaseClassName->itemText(i));
  }

  xml.writeEndElement(); //BaseClassNames
  xml.writeTextElement("SelectedBaseClassName", ui->comboBoxBaseClassName->currentText());
  xml.writeEndElement(); // Inheritance
}

void ClassGenerator::on_checkBoxInherit_toggled(bool checked)
{
  ui->widgetInheritanceProperties->setEnabled(checked);
}
