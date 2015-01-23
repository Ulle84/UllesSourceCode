/*
 * TODO
 *
 * OptionsTemplate.h -> map<replace, by> -> change function copyFromTemplate(...) of CdoeGenerator
 * Generator::generate umstellen auf CodeGenerator::copyFromTemplate
 *
 * rename Options and OptionsTemplate to DOptions and DTemplate -> D like Data???
 *
 *rename ClassGenerator -> Generator
 *  ...
 * rename Header GeneratorIterface -> GeneratorInterface ->IGenerator?
 *
 * interface generator with template?
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
#include "InterfaceGenerator.h"
#include "Generator.h"
#include "Observer.h"

CodeCreator::CodeCreator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CodeCreator),
  m_fileName("Settings.xml")
{
  ui->setupUi(this);
  m_codeGenerator = new CodeGenerator();
  initGenerators();
  readXml();
  updateComboBoxFolders();
}

CodeCreator::~CodeCreator()
{
  writeXml();
  delete m_codeGenerator;
  delete ui;
}

void CodeCreator::initGenerators()
{
  m_generators["Class"] = new ClassGenerator(m_codeGenerator, this);
  m_generators["Interface"] = new InterfaceGenerator(m_codeGenerator, this);
  m_generators["Observer"] = new Observer(m_codeGenerator, this);
  m_generators["CodeCreatorGenerator"] = new Generator(m_codeGenerator, this);

  for (auto it = m_generators.begin(); it != m_generators.end(); ++it)
  {
    if (it == m_generators.begin())
    {
      m_currentGenerator = it->second;
    }
    else
    {
      it->second->setVisible(false);
    }

    ui->comboBoxType->addItem(it->first);
    ui->generators->layout()->addWidget(it->second);
  }
}

void CodeCreator::on_comboBoxType_currentIndexChanged(const QString &type)
{
  m_currentGenerator->setVisible(false);
  m_currentGenerator = m_generators[type];
  m_currentGenerator->setVisible(true);
}

void CodeCreator::on_pushButtonSelectFolder_clicked()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("Select output folder"));

  if (directory.isEmpty())
  {
    return;
  }

  m_directories.prepend(directory);
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

  dynamic_cast<GeneratorInterface*>(m_generators[ui->comboBoxType->currentText()])->generate(ui->comboBoxFolder->currentText());
}

void CodeCreator::on_pushButtonClearHistory_clicked()
{
  m_directories.clear();
  updateComboBoxFolders();
}

bool CodeCreator::readXml()
{
  QFile file(m_fileName);

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
          m_directories.append(xml.readElementText());
        }
        else
        {
          xml.skipCurrentElement();
        }
      }
    }
    else if (m_generators.find(xml.name().toString()) != m_generators.end())
    {
      dynamic_cast<GeneratorInterface*>(m_generators.find(xml.name().toString())->second)->readXml(xml);
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
  QFile file(m_fileName);

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

  for (auto it = m_directories.begin(); it != m_directories.end(); ++it)
  {
    xml.writeTextElement("Folder", *it);
  }

  xml.writeEndElement(); // RecentFolders

  for (auto it = m_generators.begin(); it != m_generators.end(); ++it)
  {
    xml.writeStartElement(it->first);
    dynamic_cast<GeneratorInterface*>(it->second)->writeXml(xml);
    xml.writeEndElement();
  }

  xml.writeEndElement(); // Settings
  xml.writeEndDocument();

  file.close();

  return true;
}

void CodeCreator::updateComboBoxFolders()
{
  m_directories.removeDuplicates();

  ui->comboBoxFolder->clear();
  ui->comboBoxFolder->insertItems(0, m_directories);
}
