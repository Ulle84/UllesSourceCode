/*
 * TODO
 *
 * save current folder at folder selection
 *
 * Class
 *   use Q_OBJECT Macro
 *   namespace
 *   export dll
 *   members + options getter/setter
 * Data -> only header with members an inline constructor
 */

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
#include "Class.h"
#include "Generator.h"
#include "Observer.h"
#include "Interface.h"
#include "Singleton.h"
#include "Options.h"
#include "Data.h"

CodeCreator::CodeCreator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CodeCreator),
  mFileName("Settings.xml")
{
  ui->setupUi(this);
  mCodeGenerator = new CodeGenerator();
  initGenerators();
  readXml();
}

CodeCreator::~CodeCreator()
{
  writeXml();
  delete mCodeGenerator;
  delete ui;
}

void CodeCreator::copyFromTemplate(const Options &options)
{
  QDir dir(options.folderInput);

  dir.setNameFilters(options.files);

  QStringList fileNames = dir.entryList();

  for (auto it = fileNames.begin(); it != fileNames.end(); ++it)
  {
    QString filePath = dir.filePath(*it);

    QFile input(filePath);

    if (!input.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      continue;
    }

    QStringList fileContent;
    QTextStream in(&input);
    while (!in.atEnd())
    {
      QString line = in.readLine();
      for (auto it = options.searchAndReplace.begin(); it != options.searchAndReplace.end(); ++it)
      {
        line.replace(it.key(), it.value());
        line.replace(it.key().toUpper(), it.value().toUpper());
      }
      fileContent.append(line);
    }

    QString outputFileName = *it;

    for (auto it = options.searchAndReplace.begin(); it != options.searchAndReplace.end(); ++it)
    {
      outputFileName.replace(it.key(), it.value());
    }

    QFile output(options.folderOutput + QDir::separator() + outputFileName);

    if (!output.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      continue;
    }

    QTextStream out(&output);
    out << fileContent.join("\n");

    output.close();
    input.close();
  }
}

void CodeCreator::initGenerators()
{
  mGenerators["Class"] = new Class(mCodeGenerator, this);
  mGenerators["Interface"] = new Interface(mCodeGenerator, this);
  mGenerators["Observer"] = new Observer(mCodeGenerator, this);
  mGenerators["CodeCreatorGenerator"] = new Generator(mCodeGenerator, this);
  mGenerators["Singleton"] = new Singleton(mCodeGenerator, this);
  mGenerators["Data"] = new Data(mCodeGenerator, this);

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
      updateComboBoxFolders();
    }
    else if (xml.name() == "SelectedFolder")
    {
      ui->comboBoxFolder->setCurrentIndex(ui->comboBoxFolder->findText(xml.readElementText()));
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

  xml.writeTextElement("SelectedFolder", ui->comboBoxFolder->currentText());

  // generator settings
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
