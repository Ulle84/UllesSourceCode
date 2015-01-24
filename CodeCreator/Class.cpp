#include <QMessageBox>
#include <QCompleter>

#include "Class.h"
#include "ui_Class.h"

#include "Options.h"
#include "CodeGenerator.h"

Class::Class(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Class),
  mCodeGenerator(codeGenerator)
{
  ui->setupUi(this);

  QStringList templates;
  templates << "QWidget";
  templates << "QObject";

  mCompleter = new QCompleter(templates);
  ui->lineEditBaseClass->setCompleter(mCompleter);
}

Class::~Class()
{
  delete ui;
}

bool Class::generate(const QString &folder)
{
  if (ui->lineEditName->text().isEmpty())
  {
    QMessageBox mb;
    mb.setText(tr("Please enter a name!"));
    mb.exec();
    return false;
  }

  if (ui->checkBoxInherit->isChecked() && ui->lineEditBaseClass->text().isEmpty())
  {
    QMessageBox mb;
    mb.setText(tr("Please enter a base name!"));
    mb.exec();
    return false;
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
  QString baseClass = ui->lineEditBaseClass->text();
  QString include;
  QString type = ui->comboBoxType->currentText();
  options.searchAndReplace["Template"] = name;
  if (ui->checkBoxInherit->isChecked())
  {
    if (baseClass.left(1) == "Q")
    {
      include = QString("<%1>").arg(baseClass);
      options.searchAndReplace["  Template()"] = QString("  explicit %1(%2* parent = 0)").arg(name).arg(baseClass);
      options.searchAndReplace[QString("%1::%1()").arg(name)] = QString("%1::%1(%2* parent) :\n  %2(parent)").arg(name).arg(baseClass);
    }
    else
    {
      include = QString("\"%1.h\"").arg(baseClass);
    }

    options.searchAndReplace[QString("class %1").arg(name)]
        = QString("#include %1\n\nclass %2 : %3 %5").arg(include).arg(name).arg(type).arg(baseClass);
  }

  if (ui->checkBoxQObject->isChecked())
  {
    options.searchAndReplace["public:"] = "  Q_OBJECT\n\npublic:";
  }

  return mCodeGenerator->copyFromTemplate(options);
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
    else if (xml.name() == "QObject")
    {
      ui->checkBoxQObject->setChecked(xml.readElementText() == "true");
    }
    else if (xml.name() == "Inherit")
    {
      ui->checkBoxInherit->setChecked(xml.readElementText() == "true");
    }
    else if (xml.name() == "Type")
    {
      ui->comboBoxType->setCurrentIndex(ui->comboBoxType->findText(xml.readElementText()));
    }
    else if (xml.name() == "BaseClass")
    {
      ui->lineEditBaseClass->setText(xml.readElementText());
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
  xml.writeTextElement("QObject", ui->checkBoxQObject->isChecked() ? "true" : "false");
  xml.writeTextElement("Inherit", ui->checkBoxInherit->isChecked() ? "true" : "false");
  xml.writeTextElement("Type", ui->comboBoxType->currentText());
  xml.writeTextElement("BaseClass", ui->lineEditBaseClass->text());
}

void Class::on_checkBoxInherit_toggled(bool checked)
{
    ui->widgetInheritance->setEnabled(checked);
}

void Class::on_lineEditBaseClass_textEdited(const QString &text)
{
    ui->checkBoxQObject->setChecked(text.left(1) == "Q");
}
