#include <QMessageBox>
#include <QCompleter>

#include "GeneratorClass.h"
#include "ui_GeneratorClass.h"
#include "XmlHelper.h"
#include "Options.h"
#include "CodeGenerator.h"

GeneratorClass::GeneratorClass(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorClass),
  mCodeGenerator(codeGenerator)
{
  ui->setupUi(this);

  QStringList templates;
  templates << "QWidget";
  templates << "QObject";

  mCompleter = new QCompleter(templates);
  ui->lineEditBaseClass->setCompleter(mCompleter);

  ui->destructor->setDeclarationType(Class::DeclarationType::Public);
  ui->destructor->setEnabled(false);
}

GeneratorClass::~GeneratorClass()
{
  delete ui;
}

bool GeneratorClass::generate(const QString &folder)
{
  if (ui->lineEditName->text().isEmpty())
  {
    QMessageBox mb;
    mb.setText(tr("Please enter a name!"));
    mb.exec();
    return false;
  }

  return true;

  /*if (ui->checkBoxInherit->isChecked() && ui->lineEditBaseClass->text().isEmpty())
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
  options.searchAndReplace.append(qMakePair(QString("Template"), name));
  if (ui->checkBoxInherit->isChecked())
  {
    if (baseClass.left(1) == "Q")
    {
      include = "<";
      include.append(baseClass);
      include.append(">");
      options.searchAndReplace.append(qMakePair(QString("  Template()"), QString("  explicit %1(%2* parent = 0)").arg(name).arg(baseClass)));
      options.searchAndReplace.append(qMakePair(QString("%1::%1()").arg(name), QString("%1::%1(%2* parent) :\n  %2(parent)").arg(name).arg(baseClass)));
    }
    else
    {
      include = "\"";
      include.append(baseClass);
      include.append(".h\"");
    }

    options.searchAndReplace.append(qMakePair(QString("class %1").arg(name), QString("#include %1\n\nclass %2 : %3 %5").arg(include).arg(name).arg(type).arg(baseClass)));
  }

  if (ui->checkBoxQObject->isChecked())
  {
    options.searchAndReplace.append(qMakePair(QString("public:"), QString("  Q_OBJECT\n\npublic:")));
  }

  options.sortSearchAndReplaceList();

  return mCodeGenerator->copyFromTemplate(options);*/
}

void GeneratorClass::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    /*else if (xml.name() == "DisableCopy")
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
    }*/
  }
}

void GeneratorClass::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  /*XmlHelper::writeXml(xml, "DisableCopy", ui->checkBoxDisableCopy);
  XmlHelper::writeXml(xml, "UsePimpl", ui->checkBoxUsePimpl);
  XmlHelper::writeXml(xml, "QObject", ui->checkBoxQObject);
  XmlHelper::writeXml(xml, "Inherit", ui->checkBoxInherit);
  XmlHelper::writeXml(xml, "Type", ui->comboBoxType, false);
  XmlHelper::writeXml(xml, "BaseClass", ui->lineEditBaseClass);*/
}
