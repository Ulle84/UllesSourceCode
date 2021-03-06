#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QScrollBar>
#include <QStringList>
#include <QDir>
#include <QTextStream>

#include "ui_CodeCreator.h"

#include "CodeCreator.h"
#include "GeneratorAbstractFactory.h"
#include "GeneratorInterface.h"
#include "GeneratorClass.h"
#include "GeneratorTemplate.h"
#include "GeneratorDecorator.h"
#include "GeneratorObserver.h"
#include "GeneratorState.h"

CodeCreator::CodeCreator(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::CodeCreator),
  m_fileName("Settings.xml")
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "CodeCreator");

  if (m_settings->contains("windowGeometry"))
  {
    this->setGeometry(m_settings->value("windowGeometry").toRect());
  }

  initGenerators();
  readXml();
  updatePreview();

  ui->splitter->setSizes(QList<int>() << 1 << 2);
}

CodeCreator::~CodeCreator()
{
  m_settings->setValue("windowGeometry", this->geometry());
  writeXml();
  delete ui;
}

void CodeCreator::initGenerators()
{
  m_generators["AbstractFactory"] = new GeneratorAbstractFactory(this);
  m_generators["Class"] = new GeneratorClass(this);
  m_generators["Generator"] = new GeneratorTemplate(this);
  m_generators["Interface"] = new GeneratorInterface(this);
  m_generators["Decorator"] = new GeneratorDecorator(this);
  m_generators["Observer"] = new GeneratorObserver(this);
  m_generators["State"] = new GeneratorState(this);

  for (auto it = m_generators.begin(); it != m_generators.end(); it++)
  {
    if (it == m_generators.begin())
    {
      m_currentGenerator = it.value();
    }
    else
    {
      it.value()->setVisible(false);
    }

    ui->comboBoxType->addItem(it.key());
    ui->generators->layout()->addWidget(it.value());

    connect(it.value(), SIGNAL(optionsChanged()), this, SLOT(updatePreview()));
  }
}

void CodeCreator::updatePreview()
{
  QString currentFile = ui->comboBoxPreview->currentText();
  ui->comboBoxPreview->clear();

  ui->plainTextEditPreview->clear();

  GeneratorI* generator = dynamic_cast<GeneratorI*>(m_generators[ui->comboBoxType->currentText()]);

  if (!generator)
  {
    return;
  }

  QList<QPair<QString, QString> > code = generator->generatedCode();

  for (auto it = code.begin(); it != code.end(); it++)
  {
    ui->comboBoxPreview->addItem(it->first, it->second);
  }

  int index = ui->comboBoxPreview->findText(currentFile);

  if (index > -1)
  {
    ui->comboBoxPreview->setCurrentIndex(index);
  }

  // scroll to top
  /*QScrollBar* vScrollBar = ui->plainTextEditPreview->verticalScrollBar();
  vScrollBar->triggerAction(QScrollBar::SliderToMinimum);*/
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

  m_currentGenerator->setVisible(false);
  m_currentGenerator = m_generators[type];
  m_currentGenerator->setVisible(true);

  updatePreview();
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

void CodeCreator::on_pushButtonGenerate_clicked()
{
  if (ui->comboBoxFolder->currentText().isEmpty())
  {
    QMessageBox mb;
    mb.setText(tr("Folder name is empty!"));
    mb.exec();
    return;
  }

  GeneratorI* generator = dynamic_cast<GeneratorI*>(m_generators[ui->comboBoxType->currentText()]);

  if (!generator)
  {
    QMessageBox mb;
    mb.setText(tr("Internal problem!"));
    mb.exec();
    return;
    return;
  }

  QList<QPair<QString, QString> > code = generator->generatedCode();

  bool overwriteAllFiles = false;
  for (auto it = code.begin(); it != code.end(); it++)
  {
    QFile output(ui->comboBoxFolder->currentText() + QDir::separator() + it->first);

    if (output.exists() && !overwriteAllFiles)
    {      
      int response = QMessageBox::warning(this, tr("File already exist!"), tr("Do you want to overwrite the existing file %1?").arg(it->first), QMessageBox::No | QMessageBox::NoToAll | QMessageBox::Yes | QMessageBox::YesToAll, QMessageBox::No);
      if (response == QMessageBox::NoToAll)
      {
        return;
      }
      else if(response == QMessageBox::No)
      {
        continue;
      }
      else if (response == QMessageBox::YesToAll)
      {
        overwriteAllFiles = true;
      }
    }

    if (!output.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      QMessageBox mb;
      mb.setText(tr("Cannot open output file %1!").arg(it->first));
      mb.exec();
      return;
    }

    QTextStream out(&output);
    out << it->second;

    output.close();
  }

  QMessageBox messageBox;
  messageBox.setText(tr("Creation finished!"));
  messageBox.exec();
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

      updateComboBoxFolders();
    }
    else if (xml.name() == "SelectedFolder")
    {
      ui->comboBoxFolder->setCurrentIndex(ui->comboBoxFolder->findText(xml.readElementText()));
    }
    else if (m_generators.find(xml.name().toString()) != m_generators.end())
    {
      dynamic_cast<GeneratorI*>(m_generators.find(xml.name().toString()).value())->readXml(xml);
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

  xml.writeTextElement("SelectedFolder", ui->comboBoxFolder->currentText());

  // generator settings
  for (auto it = m_generators.begin(); it != m_generators.end(); ++it)
  {
    GeneratorI* generator = dynamic_cast<GeneratorI*>(it.value());

    if (generator)
    {
      xml.writeStartElement(it.key());
      generator->writeXml(xml);
      xml.writeEndElement();
    }
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

void CodeCreator::on_comboBoxPreview_currentIndexChanged(int index)
{
  ui->plainTextEditPreview->setPlainText(ui->comboBoxPreview->itemData(index).toString());
}
