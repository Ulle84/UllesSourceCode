#include <QDebug>
#include <QMessageBox>

#include "GeneratorInterface.h"
#include "ui_GeneratorInterface.h"
#include "XmlHelper.h"
#include "Class.h"
#include "Interface.h"

GeneratorInterface::GeneratorInterface(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorInterface)
{
  ui->setupUi(this);

  connect(ui->lineEditName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxPostfix, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->interfaceEditor, SIGNAL(interfaceChanged()), this, SIGNAL(optionsChanged()));
}

GeneratorInterface::~GeneratorInterface()
{
  delete ui;
}

void GeneratorInterface::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    else if (xml.name() == "Prefix")
    {
      XmlHelper::readXml(xml, ui->checkBoxPostfix);
    }
    else if (xml.name() == "Interface")
    {
      Interface interface;
      XmlHelper::readXml(xml, &interface);
      ui->interfaceEditor->setInterface(interface);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorInterface::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  XmlHelper::writeXml(xml, "Prefix", ui->checkBoxPostfix);
  XmlHelper::writeXml(xml, &ui->interfaceEditor->interface());
}

QList<QPair<QString, QString> > GeneratorInterface::generatedCode()
{
  QString interfaceName = ui->lineEditName->text();

  if (ui->checkBoxPostfix->isChecked())
  {
    if (!interfaceName.endsWith("I"))
    {
      interfaceName.append("I");
    }
  }

  Class c(interfaceName);
  c.setInterface(ui->interfaceEditor->interface(), true);

  QList<QPair<QString, QString> > code;
  code.append(qMakePair(interfaceName + ".h", c.declaration()));
  return code;
}
