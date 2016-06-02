#include <QFileDialog>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QStringList>
#include <QDir>
#include <QTextStream>

#include "CodeCreator.h"
#include "ui_CodeCreator.h"
#include "CodeGenerator.h"
#include "ClassAdvanced.h"
#include "Generator.h"
#include "Observer.h"
#include "Singleton.h"
#include "Options.h"
#include "Data.h"
#include "Decorator.h"
#include "State.h"
#include "GeneratorInterface.h"
#include "GeneratorClass.h"

CodeCreator::CodeCreator(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::CodeCreator),
  mFileName("Settings.xml")
{
  ui->setupUi(this);

  mSettings = new QSettings("Ulle", "CodeCreator");

  if (mSettings->contains("windowGeometry"))
  {
    this->setGeometry(mSettings->value("windowGeometry").toRect());
  }

  mCodeGenerator = new CodeGenerator();
  initGenerators();
  readXml();
}

CodeCreator::~CodeCreator()
{
  mSettings->setValue("windowGeometry", this->geometry());
  writeXml();
  delete mCodeGenerator;
  delete ui;
}

void CodeCreator::initGenerators()
{
  mGenerators["Class"] = new GeneratorClass(mCodeGenerator, this);
  mGenerators["ClassAdvanced"] = new ClassAdvanced(mCodeGenerator, this);
  mGenerators["Interface"] = new GeneratorInterface(mCodeGenerator, this);
  mGenerators["Observer"] = new Observer(mCodeGenerator, this);
  mGenerators["CodeCreatorGenerator"] = new Generator(mCodeGenerator, this);
  mGenerators["Singleton"] = new Singleton(mCodeGenerator, this);
  mGenerators["Data"] = new Data(mCodeGenerator, this);
  mGenerators["Decorator"] = new Decorator(mCodeGenerator, this);
  mGenerators["State"] = new State(mCodeGenerator, this);

  for (auto it = mGenerators.begin(); it != mGenerators.end(); it++)
  {
    if (it == mGenerators.begin())
    {
      mCurrentGenerator = it.value();
    }
    else
    {
      it.value()->setVisible(false);
    }

    ui->comboBoxType->addItem(it.key());
    ui->generators->layout()->addWidget(it.value());
  }
}

void CodeCreator::on_comboBoxType_currentIndexChanged(const QString& type)
{
  if (ui->comboBoxType->count() < 1)
  {
    return;
  }

  if (type.isEmpty())
  {
    ui->comboBoxType->setCurrentIndex(0);
    return;
  }

  mCurrentGenerator->setVisible(false);
  mCurrentGenerator = mGenerators[type];
  mCurrentGenerator->setVisible(true);
}

void CodeCreator::on_pushButtonSelectFolder_clicked()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("Select output folder"));

  if (directory.isEmpty())
  {
    return;
  }

  mDirectories.prepend(directory);
  updateComboBoxFolders();
}

void CodeCreator::on_pushButtonStart_clicked()
{
  if (ui->comboBoxFolder->currentText().isEmpty())
  {
    QMessageBox mb;
    mb.setText(tr("Folder name is empty!"));
    mb.exec();
    return;
  }

  if (dynamic_cast<GeneratorI*>(mGenerators[ui->comboBoxType->currentText()])->generate(ui->comboBoxFolder->currentText()))
  {
    // TODO uncomment again
    /*QMessageBox messageBox;
    messageBox.setText(tr("Creation finished!"));
    messageBox.exec();*/
  }
}

void CodeCreator::on_pushButtonClearHistory_clicked()
{
  mDirectories.clear();
  updateComboBoxFolders();
}

bool CodeCreator::readXml()
{
  QFile file(mFileName);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    return false;
  }

  QXmlStreamReader xml(&file);

  if (!xml.readNextStartElement())
  {
    return false;
  }

  if (xml.name() != "Settings")
  {
    return false;
  }

  while (xml.readNextStartElement())
  {
    if (xml.name() == "SelectedType")
    {
      ui->comboBoxType->setCurrentIndex(ui->comboBoxType->findText((xml.readElementText())));
    }
    else if (xml.name() == "RecentFolders")
    {
      while (xml.readNextStartElement())
      {
        if (xml.name() == "Folder")
        {
          mDirectories.append(xml.readElementText());
        }
        else
        {
          xml.skipCurrentElement();
        }
      }

      updateComboBoxFolders();
    }
    else if (xml.name() == "SelectedFolder")
    {
      ui->comboBoxFolder->setCurrentIndex(ui->comboBoxFolder->findText(xml.readElementText()));
    }
    else if (xml.name() == "TemplateFolder")
    {
      QString templateFolder = xml.readElementText();
      ui->lineEditTemplateFolder->setText(templateFolder);
      mCodeGenerator->setBasePath(templateFolder);
    }
    else if (mGenerators.find(xml.name().toString()) != mGenerators.end())
    {
      dynamic_cast<GeneratorI*>(mGenerators.find(xml.name().toString()).value())->readXml(xml);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }

  return true;
}

bool CodeCreator::writeXml()
{
  QFile file(mFileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    return false;
  }

  QXmlStreamWriter xml(&file);
  xml.setAutoFormatting(true);
  xml.setAutoFormattingIndent(2);
  xml.writeStartDocument();

  xml.writeStartElement("Settings");

  xml.writeTextElement("SelectedType", ui->comboBoxType->currentText());

  xml.writeStartElement("RecentFolders");

  for (auto it = mDirectories.begin(); it != mDirectories.end(); ++it)
  {
    xml.writeTextElement("Folder", *it);
  }

  xml.writeEndElement(); // RecentFolders

  xml.writeTextElement("SelectedFolder", ui->comboBoxFolder->currentText());
  xml.writeTextElement("TemplateFolder", ui->lineEditTemplateFolder->text());

  // generator settings
  for (auto it = mGenerators.begin(); it != mGenerators.end(); ++it)
  {
    xml.writeStartElement(it.key());
    dynamic_cast<GeneratorI*>(it.value())->writeXml(xml);
    xml.writeEndElement();
  }

  xml.writeEndElement(); // Settings
  xml.writeEndDocument();

  file.close();

  return true;
}

void CodeCreator::updateComboBoxFolders()
{
  mDirectories.removeDuplicates();

  ui->comboBoxFolder->clear();
  ui->comboBoxFolder->insertItems(0, mDirectories);
}

void CodeCreator::on_pushButtonSelectTemplateFolder_clicked()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("Select template folder"));

  if (directory.isEmpty())
  {
    return;
  }

  ui->lineEditTemplateFolder->setText(directory); // TODO relative path?
  mCodeGenerator->setBasePath(directory);
}
