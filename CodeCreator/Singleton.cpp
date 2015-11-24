#include <QMessageBox>

#include "Singleton.h"
#include "ui_Singleton.h"
#include "XmlHelper.h"
#include "Options.h"
#include "CodeGenerator.h"

Singleton::Singleton(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Singleton),
  m_codeGenerator(codeGenerator)
{
  ui->setupUi(this);
}

Singleton::~Singleton()
{
  delete ui;
}

bool Singleton::generate(const QString &folder)
{
  if (ui->lineEditName->text().isEmpty())
  {
    QMessageBox messageBox;
    messageBox.setText(tr("Please enter a name!"));
    messageBox.exec();
    return false;
  }

  Options options;
  options.folderOutput = folder;

  options.searchAndReplace["Singleton"] = ui->lineEditName->text();

  options.files << "Singleton.cpp";
  options.files << "Singleton.h";

  if (ui->comboBoxType->currentText() == "lazy")
  {
    options.folderInput = "Singleton/lazy/";
  }
  else
  {
    options.folderInput = "Singleton/eager/";
  }

  return m_codeGenerator->copyFromTemplate(options);
}

void Singleton::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    else if (xml.name() == "Type")
    {
      XmlHelper::readXml(xml, ui->comboBoxType);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void Singleton::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  XmlHelper::writeXml(xml, "Type", ui->comboBoxType, false);
}
