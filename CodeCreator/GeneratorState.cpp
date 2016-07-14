#include "ui_GeneratorState.h"

#include "Class.h"
#include "GeneratorState.h"
#include "MethodGui.h"
#include "StringHelper.h"
#include "WidgetListEditor.h"
#include "XmlHelper.h"

GeneratorState::GeneratorState(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorState),
  m_widgetListEditor(NULL)
{
  ui->setupUi(this);

  connect(ui->lineEditState, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
  connect(ui->lineEditContext, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));

  connect(ui->checkBoxState, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxContext, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxInterface, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));
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
      XmlHelper::readXml(xml, &m_interface);
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
  XmlHelper::writeXml(xml, &m_interface);

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

void GeneratorState::on_pushButtonInterface_clicked()
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

void GeneratorState::addMethod()
{
  MethodGui* methodGui = new MethodGui();
  methodGui->setTypeVisible(false);
  methodGui->setDeclarationTypeVisible(false);
  dynamic_cast<WidgetListEditor*>(QObject::sender())->addItem(methodGui);
}

void GeneratorState::fillMethodList()
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
