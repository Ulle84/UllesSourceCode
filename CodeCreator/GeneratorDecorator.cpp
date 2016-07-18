#include <QDebug>

#include "ui_GeneratorDecorator.h"

#include "Class.h"
#include "GeneratorDecorator.h"
#include "XmlHelper.h"
#include "Interface.h"
#include "Method.h"
#include "WidgetListEditor.h"
#include "MethodGui.h"
#include "StringHelper.h"

GeneratorDecorator::GeneratorDecorator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorDecorator)
{
  ui->setupUi(this);

  connect(ui->lineEditComponent, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
  connect(ui->lineEditDecorator, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));

  connect(ui->checkBoxComponent, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxDecorator, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxInterface, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));

  connect(ui->interfaceEditor, SIGNAL(interfaceChanged()), this, SIGNAL(optionsChanged()));
}

GeneratorDecorator::~GeneratorDecorator()
{
  delete ui;
}

void GeneratorDecorator::readXml(QXmlStreamReader &xml)
{
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Component")
    {
      XmlHelper::readXml(xml, ui->lineEditComponent);
    }
    else if(xml.name() == "Decorator")
    {
      XmlHelper::readXml(xml, ui->lineEditDecorator);
    }
    else if (xml.name() == "Interface")
    {
      Interface interface;
      XmlHelper::readXml(xml, &interface);
      ui->interfaceEditor->setInterface(interface);
    }
    else if(xml.name() == "CreateComponent")
    {
      XmlHelper::readXml(xml, ui->checkBoxComponent);
    }
    else if(xml.name() == "CreateDecorator")
    {
      XmlHelper::readXml(xml, ui->checkBoxDecorator);
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

void GeneratorDecorator::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Component", ui->lineEditComponent);
  XmlHelper::writeXml(xml, "Decorator", ui->lineEditDecorator);
  XmlHelper::writeXml(xml, &ui->interfaceEditor->interface());

  XmlHelper::writeXml(xml, "CreateComponent", ui->checkBoxComponent);
  XmlHelper::writeXml(xml, "CreateDecorator", ui->checkBoxDecorator);
  XmlHelper::writeXml(xml, "CreateInterface", ui->checkBoxInterface);
}

QList<QPair<QString, QString> > GeneratorDecorator::generatedCode()
{
  QList<QPair<QString, QString> > generatedCode;

  QString decoratorName = ui->lineEditDecorator->text();
  QString componentName = ui->lineEditComponent->text();
  QString interfaceName = ui->lineEditComponent->text() + "I";

  Interface interface = ui->interfaceEditor->interface();
  interface.setName(interfaceName);

  QList<Interface> interfaces;
  interfaces.append(interface);

  if (ui->checkBoxInterface->isChecked())
  {
    Class c(interfaceName);
    c.setInterface(interface, true);

    generatedCode.append(qMakePair(interfaceName + ".h", c.declaration()));
  }

  if (ui->checkBoxComponent->isChecked())
  {
    Class c(componentName);
    c.setInterfaces(interfaces);

    generatedCode.append(qMakePair(componentName + ".h", c.declaration()));
    generatedCode.append(qMakePair(componentName + ".cpp", c.implementation()));
  }

  if (ui->checkBoxDecorator->isChecked())
  {
    Class c(decoratorName);
    c.setInterfaces(interfaces);

    Member member;
    member.setType(interfaceName + "*");
    member.setName(StringHelper::lowerCaseFirstLetter(componentName));

    Members members;
    members.append(member);
    c.setMembers(members);

    QString declarationString = decoratorName;
    declarationString.append("(");
    declarationString.append(member.type());
    declarationString.append(" ");
    declarationString.append(member.name());
    declarationString.append(");");

    Declaration declaration;
    declaration.setDeclaration(declarationString);

    Declarations declarations;
    declarations.append(declaration);
    c.setAdditionalDeclarations(declarations);

    QString code = decoratorName;
    code.append("::");
    code.append(decoratorName);
    code.append("(");
    code.append(member.type());
    code.append(" ");
    code.append(member.name());
    code.append(") :\n  ");
    code.append(member.nameWithPrefix());
    code.append("(");
    code.append(member.name());
    code.append(")\n{\n}");

    c.setAdditionalImplementations(QStringList() << code);

    generatedCode.append(qMakePair(decoratorName + ".h", c.declaration()));
    generatedCode.append(qMakePair(decoratorName + ".cpp", c.implementation()));
  }

  return generatedCode;
}
