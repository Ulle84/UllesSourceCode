#include "ui_GeneratorState.h"

#include "Class.h"
#include "GeneratorState.h"
#include "MethodGui.h"
#include "StringHelper.h"
#include "XmlHelper.h"

GeneratorState::GeneratorState(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorState)
{
  ui->setupUi(this);

  connect(ui->lineEditState, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
  connect(ui->lineEditContext, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));

  connect(ui->checkBoxState, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxContext, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxInterface, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));

  connect(ui->interfaceEditor, SIGNAL(interfaceChanged()), this, SIGNAL(optionsChanged()));
}

GeneratorState::~GeneratorState()
{
  delete ui;
}

void GeneratorState::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "State")
    {
      XmlHelper::readXml(xml, ui->lineEditState);
    }
    else if(xml.name() == "Context")
    {
      XmlHelper::readXml(xml, ui->lineEditContext);
    }
    else if (xml.name() == "Interface")
    {
      Interface interface;
      XmlHelper::readXml(xml, &interface);
      ui->interfaceEditor->setInterface(interface);
    }
    else if(xml.name() == "CreateState")
    {
      XmlHelper::readXml(xml, ui->checkBoxState);
    }
    else if(xml.name() == "CreateContext")
    {
      XmlHelper::readXml(xml, ui->checkBoxContext);
    }
    else if(xml.name() == "CreateInterface")
    {
      XmlHelper::readXml(xml, ui->checkBoxInterface);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorState::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "State", ui->lineEditState);
  XmlHelper::writeXml(xml, "Context", ui->lineEditContext);
  Interface interface = ui->interfaceEditor->interface();
  XmlHelper::writeXml(xml, &interface);

  XmlHelper::writeXml(xml, "CreateState", ui->checkBoxState);
  XmlHelper::writeXml(xml, "CreateContext", ui->checkBoxContext);
  XmlHelper::writeXml(xml, "CreateInterface", ui->checkBoxInterface);
}

QList<QPair<QString, QString> > GeneratorState::generatedCode()
{
  QList<QPair<QString, QString> > code;

  QString ContextName = ui->lineEditContext->text();
  QString StateName = ui->lineEditState->text();
  QString interfaceName = ui->lineEditState->text() + "I";

  Interface interface;
  interface.setName(interfaceName);

  QList<Interface> interfaces;
  interfaces.append(interface);

  if (ui->checkBoxInterface->isChecked())
  {
    Class c(interfaceName);
    c.setInterface(interface, true);

    code.append(qMakePair(interfaceName + ".h", c.declaration()));
  }

  if (ui->checkBoxState->isChecked())
  {
    Class c(StateName);
    c.setInterfaces(interfaces);

    code.append(qMakePair(StateName + ".h", c.declaration()));
    code.append(qMakePair(StateName + ".cpp", c.implementation()));
  }

  if (ui->checkBoxContext->isChecked())
  {
    Class c(ContextName);
    c.setInterfaces(interfaces);

    Member member;
    member.setType(interfaceName + "*");
    member.setName(StringHelper::lowerCaseFirstLetter(StateName));
    Members members;
    members.append(member);

    c.setMembers(members);

    code.append(qMakePair(ContextName + ".h", c.declaration()));
    code.append(qMakePair(ContextName + ".cpp", c.implementation()));
  }

  return code;
}
