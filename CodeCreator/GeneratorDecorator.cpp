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
  ui(new Ui::GeneratorDecorator),
  m_widgetListEditor(NULL)
{
  ui->setupUi(this);

  connect(ui->lineEditComponent, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
  connect(ui->lineEditDecorator, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));

  connect(ui->checkBoxComponent, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxDecorator, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxInterface, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));
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
      XmlHelper::readXml(xml, &m_interface);
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
  XmlHelper::writeXml(xml, &m_interface);

  XmlHelper::writeXml(xml, "CreateComponent", ui->checkBoxComponent);
  XmlHelper::writeXml(xml, "CreateDecorator", ui->checkBoxDecorator);
  XmlHelper::writeXml(xml, "CreateInterface", ui->checkBoxInterface);
}

QList<QPair<QString, QString> > GeneratorDecorator::generatedCode()
{
  QList<QPair<QString, QString> > code;

  QString decoratorName = ui->lineEditDecorator->text();
  QString componentName = ui->lineEditComponent->text();
  QString interfaceName = ui->lineEditComponent->text() + "I";
  m_interface.setName(interfaceName);

  QList<Interface> interfaces;
  interfaces.append(m_interface);

  if (ui->checkBoxInterface->isChecked())
  {
    Class c(interfaceName);

    c.setConstructorDeclarationType(Class::DeclarationType::NoDeclaration);
    c.setDeclareDestructorVirtual(true);

    m_interface.setAllMethodsPublicPureVirtual();
    c.setInterface(m_interface);

    code.append(qMakePair(interfaceName + ".h", c.declaration()));
  }

  if (ui->checkBoxComponent->isChecked())
  {
    Class c(componentName);
    c.setInterfaces(interfaces);

    code.append(qMakePair(componentName + ".h", c.declaration()));
    code.append(qMakePair(componentName + ".cpp", c.implementation()));
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

    code.append(qMakePair(decoratorName + ".h", c.declaration()));
    code.append(qMakePair(decoratorName + ".cpp", c.implementation()));
  }

  return code;
}

void GeneratorDecorator::on_pushButtonInterface_clicked()
{
  if (m_widgetListEditor == NULL)
  {
    m_widgetListEditor = new WidgetListEditor(this);
    m_widgetListEditor->setButtonText(tr("add method"));
    m_widgetListEditor->setWindowTitle(tr("interface editor"));
    connect(m_widgetListEditor, SIGNAL(addClicked()), this, SLOT(addMethod()));
    fillMethodList();
  }

  if (m_widgetListEditor->exec() == QDialog::Accepted)
  {
    m_interface.clear();

    QList<QWidget*> items = m_widgetListEditor->items();

    for (auto it = items.begin(); it != items.end(); it++)
    {
      MethodGui* methodGui = dynamic_cast<MethodGui*>(*it);
      if (methodGui)
      {
        m_interface.append(methodGui->method());
      }
    }

    emit optionsChanged();
  }
  else
  {
    m_widgetListEditor->clear();
    fillMethodList();
  }
}

void GeneratorDecorator::addMethod()
{
  MethodGui* methodGui = new MethodGui();
  methodGui->setTypeVisible(false);
  methodGui->setDeclarationTypeVisible(false);
  dynamic_cast<WidgetListEditor*>(QObject::sender())->addItem(methodGui);
}

void GeneratorDecorator::fillMethodList()
{
  for (auto it = m_interface.begin(); it != m_interface.end(); it++)
  {
    MethodGui* methodGui = new MethodGui();
    methodGui->setTypeVisible(false);
    methodGui->setDeclarationTypeVisible(false);
    methodGui->setMethod(*it);
    m_widgetListEditor->addItem(methodGui);
  }
}
