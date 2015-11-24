#include <QMessageBox>
#include <QCompleter>

#include "Class.h"
#include "ui_Class.h"
#include "XmlHelper.h"
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
      options.folderInput = "Class/pImplNoCopy/";
    }
    else
    {
      options.folderInput = "Class/pImpl/";
    }
  }
  else
  {
    if (ui->checkBoxDisableCopy->isChecked())
    {
      options.folderInput = "Class/noCopy/";
    }
    else
    {
      options.folderInput = "Class/base/";
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
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    else if (xml.name() == "DisableCopy")
    {
      XmlHelper::readXml(xml, ui->checkBoxDisableCopy);
    }
    else if (xml.name() == "UsePimpl")
    {
      XmlHelper::readXml(xml, ui->checkBoxUsePimpl);
    }
    else if (xml.name() == "QObject")
    {
      XmlHelper::readXml(xml, ui->checkBoxQObject);
    }
    else if (xml.name() == "Inherit")
    {
      XmlHelper::readXml(xml, ui->checkBoxInherit);
    }
    else if (xml.name() == "Type")
    {
      XmlHelper::readXml(xml, ui->comboBoxType);
    }
    else if (xml.name() == "BaseClass")
    {
      XmlHelper::readXml(xml, ui->lineEditBaseClass);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Class::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  XmlHelper::writeXml(xml, "DisableCopy", ui->checkBoxDisableCopy);
  XmlHelper::writeXml(xml, "UsePimpl", ui->checkBoxUsePimpl);
  XmlHelper::writeXml(xml, "QObject", ui->checkBoxQObject);
  XmlHelper::writeXml(xml, "Inherit", ui->checkBoxInherit);
  XmlHelper::writeXml(xml, "Type", ui->comboBoxType, false);
  XmlHelper::writeXml(xml, "BaseClass", ui->lineEditBaseClass);
}

void Class::on_checkBoxInherit_toggled(bool checked)
{
    ui->widgetInheritance->setEnabled(checked);
}

void Class::on_lineEditBaseClass_textEdited(const QString &text)
{
    ui->checkBoxQObject->setChecked(text.left(1) == "Q");
}
