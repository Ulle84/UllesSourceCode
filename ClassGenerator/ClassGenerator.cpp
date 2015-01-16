/*
 * TODO
 * inherit from inheritage type (private, public, protected)
 * use Q_OBJECT Macro
 * make constructor private
 * arguments of constructor
 */

#include "ClassGenerator.h"
#include "ui_ClassGenerator.h"

#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QXmlStreamWriter>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QFile>

ClassGenerator::ClassGenerator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::ClassGenerator),
  m_fileName("RecentFolders.xml")
{
  ui->setupUi(this);
  fromXml();
  updateComboBoxFolders();
}

ClassGenerator::~ClassGenerator()
{
  toXml();
  delete ui;
}

void ClassGenerator::on_pushButtonSelectFolder_clicked()
{
  QString directory = QFileDialog::getExistingDirectory(this, tr("Select output folder"));

  if (directory.isEmpty())
  {
    return;
  }

  m_directories.prepend(directory);
  updateComboBoxFolders();
}

void ClassGenerator::on_pushButtonStart_clicked()
{
  m_className = ui->lineEditClassName->text();

  if (m_className.isEmpty())
  {
    QMessageBox mb;
    mb.setText(tr("File name is empty!"));
    mb.exec();
    return;
  }

  QString fileNameHeader = ui->comboBoxFolder->currentText() + QDir::separator() + m_className + ".h";
  bool headerCreated = saveCode(fileNameHeader, generateCodeHeader());

  QString fileNameClass = ui->comboBoxFolder->currentText() + QDir::separator() + m_className + ".cpp";
  bool classCreated = saveCode(fileNameClass, generateCodeClass());

  if (headerCreated)
  {
    QMessageBox mb;
    mb.setText(tr("Files were successfully created!")); //TODO show list of created files?
    mb.exec();
    return;
  }
}

bool ClassGenerator::toXml()
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

  xml.writeStartElement("RecentFolders");

  xml.writeTextElement("ClassName", ui->lineEditClassName->text());

  for (auto it = m_directories.begin(); it != m_directories.end(); ++it)
  {
    xml.writeTextElement("Folder", *it);
  }

  xml.writeEndElement(); // RecentFolders
  xml.writeEndDocument();

  file.close();

  return true;
}

bool ClassGenerator::fromXml()
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

  if (xml.name() != "RecentFolders")
  {
    return false;
  }

  while (xml.readNextStartElement())
  {
    if (xml.name() == "Folder")
    {
      m_directories.append(xml.readElementText());
    }
    else if (xml.name() == "ClassName")
    {
     ui->lineEditClassName->setText(xml.readElementText());
    }
    else
    {
      xml.skipCurrentElement();
    }
  }

  return true;
}

void ClassGenerator::updateComboBoxFolders()
{
  m_directories.removeDuplicates();

  ui->comboBoxFolder->clear();
  ui->comboBoxFolder->insertItems(0, m_directories);
}

bool ClassGenerator::saveCode(const QString &fileName, const QStringList &content)
{
  QFile file(fileName);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    return false;
  }

  qint64 bytesWritten = file.write(content.join("\n").toStdString().c_str());

  file.close();

  return bytesWritten == -1 ? false : true;
}

QStringList ClassGenerator::generateCodeHeader()
{
  QStringList code;
  code.append(QString("#ifndef %1_H").arg(m_className.toUpper()));
  code.append(QString("#define %1_H").arg(m_className.toUpper()));
  code.append(QString(""));

  if (ui->checkBoxUsePimpl->isChecked())
  {
    code.append(QString("#include <memory>"));
    code.append(QString(""));
  }

  code.append(QString("class %1").arg(m_className));
  code.append(QString("{"));
  code.append(QString("public:"));
  code.append(QString("  %1();").arg(m_className));
  code.append(QString("  ~%1();").arg(m_className));

  if (ui->checkBoxDisableCopy->isChecked() || ui->checkBoxUsePimpl->isChecked())
  {
    code.append(QString(""));
    code.append(QString("private:"));
  }

  if (ui->checkBoxDisableCopy->isChecked())
  {
    code.append(QString("  %1(const %2&);").arg(m_className).arg(m_className));
    code.append(QString("  %1& operator=(const %2 &);").arg(m_className).arg(m_className));
  }

  if (ui->checkBoxDisableCopy->isChecked() && ui->checkBoxUsePimpl->isChecked())
  {
    code.append(QString(""));
  }

  if (ui->checkBoxUsePimpl->isChecked())
  {
    code.append(QString("class %1Impl;").arg(m_className));
    code.append(QString("std::unique_ptr<%1Impl> m_pImpl;").arg(m_className));
  }

  code.append(QString("};"));
  code.append(QString(""));

  //code.append(QString(""));
  //code.append(QString("%1").arg(m_className));
  //code.append(QString("%1%2").arg(m_className).arg(m_className));

  code.append(QString("#endif // %1_H").arg(m_className.toUpper()));

  return code;
}

QStringList ClassGenerator::generateCodeClass()
{
  QStringList code;
  code.append(QString("#include \"%1.h\"").arg(m_className));
  code.append(QString(""));
  code.append(QString("%1::%2()").arg(m_className).arg(m_className));
  code.append(QString("{"));
  code.append(QString("}"));

  code.append(QString("%1::~%2()").arg(m_className).arg(m_className));
  code.append(QString("{"));
  code.append(QString("}"));

  /*
  #include "ClassGenerator.h"
  ClassGenerator::ClassGenerator()
  {
  }
  ~ClassGenerator::ClassGenerator()
  {
  }
  */

  //code.append(QString(""));
  //code.append(QString("%1").arg(m_className));
  //code.append(QString("%1%2").arg(m_className).arg(m_className));

  return code;
}
