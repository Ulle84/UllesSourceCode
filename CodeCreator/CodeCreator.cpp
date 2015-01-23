/*
 * TODO
 *
 *
 *
 *rename ClassGenerator -> Generator
 *  ...
 * rename Header GeneratorIterface -> GeneratorInterface ->IGenerator?
 *
 *
 * Class
 *   use Q_OBJECT Macro
 *   namespace
 *   export dll
 *   members + options getter/setter
 * Singleton
 */

#include <QFileDialog>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>

#include "CodeCreator.h"
#include "ui_CodeCreator.h"
#include "CodeGenerator.h"
#include "ClassGenerator.h"
#include "Generator.h"
#include "Observer.h"
#include "Interface.h"

CodeCreator::CodeCreator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CodeCreator),
  mFileName("Settings.xml")
{
  ui->setupUi(this);
  mCodeGenerator = new CodeGenerator();
  initGenerators();
  readXml();
  updateComboBoxFolders();
}

CodeCreator::~CodeCreator()
{
  writeXml();
  delete mCodeGenerator;
  delete ui;
}

void CodeCreator::initGenerators()
{
  mGenerators["Class"] = new ClassGenerator(mCodeGenerator, this);
  mGenerators["Interface"] = new Interface(mCodeGenerator, this);
  mGenerators["Observer"] = new Observer(mCodeGenerator, this);
  mGenerators["CodeCreatorGenerator"] = new Generator(mCodeGenerator, this);

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

void CodeCreator::on_comboBoxType_currentIndexChanged(const QString &type)
{
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

  dynamic_cast<IGenerator*>(mGenerators[ui->comboBoxType->currentText()])->generate(ui->comboBoxFolder->currentText());
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
    }
    else if (mGenerators.find(xml.name().toString()) != mGenerators.end())
    {
      dynamic_cast<IGenerator*>(mGenerators.find(xml.name().toString()).value())->readXml(xml);
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

  for (auto it = mGenerators.begin(); it != mGenerators.end(); ++it)
  {
    xml.writeStartElement(it.key());
    dynamic_cast<IGenerator*>(it.value())->writeXml(xml);
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
