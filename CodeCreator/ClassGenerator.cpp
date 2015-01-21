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
  if (ui->lineEditClassName->text().isEmpty())
  {
    QMessageBox mb;
    mb.setText(tr("File name is empty!"));
    mb.exec();
    return;
  }

  Options options;
  options.m_type = Options::Class;
  options.m_useInheritance = ui->checkBoxInherit->isChecked();
  options.m_usePimpl = ui->checkBoxUsePimpl->isChecked();
  options.m_disableCopy = ui->checkBoxDisableCopy->isChecked();
  options.m_className = ui->lineEditClassName->text();
  options.m_inheritanceType = ui->comboBoxType->currentText();
  options.m_baseClassName = ui->comboBoxBaseClassName->currentText();

  m_codeGenerator->generateCode(options);

  /*QString fileNameHeader = ui->comboBoxFolder->currentText() + QDir::separator() + m_className + ".h";
  bool headerCreated = m_codeSaver->saveCode(fileNameHeader, generateCodeHeader());

  QString fileNameClass = ui->comboBoxFolder->currentText() + QDir::separator() + m_className + ".cpp";
  bool classCreated = m_codeSaver->saveCode(fileNameClass, generateCodeClass());

  if (ui->checkBoxUsePimpl->isChecked())
  {
    QString fileNamePimpl = ui->comboBoxFolder->currentText() + QDir::separator() + m_className + "Impl.h";
    bool pimplCreated = m_codeSaver->saveCode(fileNamePimpl, generateCodePimpl());
  }

  if (headerCreated)
  {
    QMessageBox mb;
    mb.setText(tr("Files were successfully created!")); //TODO show list of created files?
    mb.exec();
    return;
  }*/
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

  xml.writeStartElement("Settings");
  xml.writeTextElement("ClassName", ui->lineEditClassName->text());
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

  xml.writeStartElement("RecentFolders");

  for (auto it = m_directories.begin(); it != m_directories.end(); ++it)
  {
    xml.writeTextElement("Folder", *it);
  }

  xml.writeEndElement(); // RecentFolders

  xml.writeEndElement(); // Settings
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

  if (xml.name() != "Settings")
  {
    return false;
  }

  while (xml.readNextStartElement())
  {
    if (xml.name() == "ClassName")
    {
      ui->lineEditClassName->setText(xml.readElementText());
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

void ClassGenerator::on_pushButtonClearHistory_clicked()
{
  m_directories.clear();
  updateComboBoxFolders();
}

void ClassGenerator::on_checkBoxInherit_toggled(bool checked)
{
  ui->widgetInheritanceProperties->setEnabled(checked);
}

/*QStringList ClassGenerator::generateCodeHeader()
{


  m_codeGenerator->generateCodeHeader(options);

  QStringList code;
  code.append(QString("#ifndef %1_H").arg(m_className.toUpper()));
  code.append(QString("#define %1_H").arg(m_className.toUpper()));
  code.append(QString(""));

  if (ui->checkBoxInherit->isChecked())
  {
    QString baseClassName = ui->comboBoxBaseClassName->currentText();
    code.append(QString("#include \"%1.h\"").arg(baseClassName));
    code.append(QString(""));
    code.append(QString("class %1 : %2 %3").arg(m_className).arg(ui->comboBoxType->currentText()).arg(baseClassName));
  }
  else
  {
    code.append(QString("class %1").arg(m_className));
  }

  code.append(QString("{"));
  code.append(QString("public:"));
  code.append(QString("  %1();").arg(m_className));

  if (ui->checkBoxUsePimpl->isChecked() && !ui->checkBoxDisableCopy->isChecked())
  {
    code.append(QString("  %1(const %1& rhs);").arg(m_className));
    code.append(QString("  %1(%1&& rhs);").arg(m_className));
    code.append(QString("  %1& operator=(const %1& rhs);").arg(m_className));
  }

  code.append(QString("  ~%1();").arg(m_className));

  if (ui->checkBoxDisableCopy->isChecked() || ui->checkBoxUsePimpl->isChecked())
  {
    code.append(QString(""));
    code.append(QString("private:"));
  }

  if (ui->checkBoxDisableCopy->isChecked())
  {
    code.append(QString("  %1(const %1& rhs);").arg(m_className));
    code.append(QString("  %1(%1&& rhs);").arg(m_className));
    code.append(QString("  %1& operator=(const %1& rhs);").arg(m_className));
  }

  if (ui->checkBoxDisableCopy->isChecked() && ui->checkBoxUsePimpl->isChecked())
  {
    code.append(QString(""));
  }

  if (ui->checkBoxUsePimpl->isChecked())
  {
    code.append(QString("  class %1Impl;").arg(m_className));
    code.append(QString("  %1Impl* m_pImpl;").arg(m_className));
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

  // includes
  code.append(QString("#include \"%1.h\"").arg(m_className));

  if (ui->checkBoxUsePimpl->isChecked())
  {
    code.append(QString("#include \"%1Impl.h\"").arg(m_className));
    code.append(QString(""));
    code.append(QString("#include <utility>"));
  }

  code.append(QString(""));

  // constructor
  code.append(QString("%1::%1()").arg(m_className));

  if (ui->checkBoxUsePimpl->isChecked())
  {
    code.append(QString("  : m_pImpl(new %1Impl())").arg(m_className));
  }

  code.append(QString("{"));
  code.append(QString("}"));
  code.append(QString(""));

  if (ui->checkBoxUsePimpl->isChecked())
  {
    // copy constructor
    code.append(QString("%1::%1(const %1& rhs)").arg(m_className));
    code.append(QString("  : m_pImpl(new %1Impl(*rhs.m_pImpl))").arg(m_className));
    code.append(QString("{"));
    code.append(QString("}"));
    code.append(QString(""));

    // move constructor
    code.append(QString("%1::%1(%1&& rhs)").arg(m_className));
    code.append(QString("  : m_pImpl(nullptr)"));
    code.append(QString("{"));
    code.append(QString("  std::swap(m_pImpl, rhs.m_pImpl);"));
    code.append(QString("}"));
    code.append(QString(""));

    // assignment operator
    code.append(QString("%1& %1::operator=(const %1& rhs)").arg(m_className));
    code.append(QString("{"));
    code.append(QString("  if(this != &rhs)"));
    code.append(QString("  {"));
    code.append(QString("    *m_pImpl = *(rhs.m_pImpl);"));
    code.append(QString("  }"));
    code.append(QString("  return *this;"));
    code.append(QString("}"));
    code.append(QString(""));
  }

  // destructor
  code.append(QString("%1::~%1()").arg(m_className));
  code.append(QString("{"));

  if (ui->checkBoxUsePimpl->isChecked())
  {
    code.append(QString("  delete m_pImpl;"));
  }

  code.append(QString("}"));

  return code;
}

QStringList ClassGenerator::generateCodePimpl()
{
  QStringList code;
  code.append(QString("#ifndef %1IMPL_H").arg(m_className.toUpper()));
  code.append(QString("#define %1IMPL_H").arg(m_className.toUpper()));
  code.append(QString(""));
  code.append(QString("#include \"%1.h\"").arg(m_className));
  code.append(QString(""));
  code.append(QString("class %1::%1Impl").arg(m_className));
  code.append(QString("{"));
  code.append(QString("public:"));
  code.append(QString(""));
  code.append(QString("};"));
  code.append(QString(""));

  //code.append(QString(""));
  //code.append(QString("%1").arg(m_className));

  code.append(QString("#endif // %1IMPL_H").arg(m_className.toUpper()));

  return code;
}*/
