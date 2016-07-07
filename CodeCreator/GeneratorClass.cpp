#include <QDebug>
#include <QMessageBox>
#include <QCompleter>

#include "GeneratorClass.h"
#include "ui_GeneratorClass.h"
#include "XmlHelper.h"
#include "Options.h"
#include "CodeGenerator.h"
#include "Class.h"
#include "Interface.h"
#include "InterfaceGui.h"
#include "WidgetListEditor.h"

GeneratorClass::GeneratorClass(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorClass),
  m_widgetListEditor(NULL)
{
  ui->setupUi(this);

  QStringList templates;
  templates << "QWidget";
  templates << "QObject";

  m_completer = new QCompleter(templates);
  ui->lineEditBaseClass->setCompleter(m_completer);

  ui->constructor->setDeclarationType(Class::DeclarationType::Public);
  ui->destructor->setDeclarationType(Class::DeclarationType::Public);

  setConnections();
}

void GeneratorClass::setConnections()
{
  connect(ui->lineEditName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
  connect(ui->lineEditBaseClass, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));

  connect(ui->constructor, SIGNAL(declarationTypeChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->destructor, SIGNAL(declarationTypeChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->copyConstructor, SIGNAL(declarationTypeChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->copyOperator, SIGNAL(declarationTypeChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->moveConstructor, SIGNAL(declarationTypeChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->moveOperator, SIGNAL(declarationTypeChanged(int)), this, SIGNAL(optionsChanged()));

  connect(ui->dPointer, SIGNAL(dPointerTypeChanged(int)), this, SIGNAL(optionsChanged()));
  connect(ui->singleton, SIGNAL(singletonTypeChanged(int)), this, SIGNAL(optionsChanged()));

  connect(ui->checkBoxQObjectMacro, SIGNAL(clicked(bool)), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxVirtualDesctructor, SIGNAL(clicked(bool)), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxExplicitConstructor, SIGNAL(clicked(bool)), this, SIGNAL(optionsChanged()));

  connect(ui->plainTextEditNamespaces, SIGNAL(textChanged()), this, SIGNAL(optionsChanged()));

  // TODO interface change
}

GeneratorClass::~GeneratorClass()
{
  delete ui;
}

void GeneratorClass::readXml(QXmlStreamReader &xml)
{
  // TODO can this be be done with QMap<String, XmlBlubI> ?
  while (xml.readNextStartElement())
  {
    if (xml.name() == "Name")
    {
      XmlHelper::readXml(xml, ui->lineEditName);
    }
    else if (xml.name() == "BaseClass")
    {
      XmlHelper::readXml(xml, ui->lineEditBaseClass);
    }
    else if (xml.name() == "ConstructorDeclaration")
    {
      XmlHelper::readXml(xml, ui->constructor);
    }
    else if (xml.name() == "DestructorDeclaration")
    {
      XmlHelper::readXml(xml, ui->destructor);
    }
    else if (xml.name() == "CopyConstructorDeclaration")
    {
      XmlHelper::readXml(xml, ui->copyConstructor);
    }
    else if (xml.name() == "CopyOperatorDeclaration")
    {
      XmlHelper::readXml(xml, ui->copyOperator);
    }
    else if (xml.name() == "MoveConstructorDeclaration")
    {
      XmlHelper::readXml(xml, ui->moveConstructor);
    }
    else if (xml.name() == "MoveOperatorDeclaration")
    {
      XmlHelper::readXml(xml, ui->moveOperator);
    }
    else if (xml.name() == "SingletonType")
    {
      XmlHelper::readXml(xml, ui->singleton);
    }
    else if (xml.name() == "DPointerType")
    {
      XmlHelper::readXml(xml, ui->dPointer);
    }
    else if (xml.name() == "QObjectMacro")
    {
      XmlHelper::readXml(xml, ui->checkBoxQObjectMacro);
    }
    else if (xml.name() == "VirtualDestructor")
    {
      XmlHelper::readXml(xml, ui->checkBoxVirtualDesctructor);
    }
    else if (xml.name() == "ExplicitConstructor")
    {
      XmlHelper::readXml(xml, ui->checkBoxExplicitConstructor);
    }
    else if (xml.name() == "Namespaces")
    {
      XmlHelper::readXml(xml, ui->plainTextEditNamespaces);
    }
    else if (xml.name() == "Interfaces")
    {
      XmlHelper::readXml(xml, &m_interfaces);
    }
    else
    {
      xml.skipCurrentElement();
    }
  }
}

void GeneratorClass::writeXml(QXmlStreamWriter &xml)
{
  XmlHelper::writeXml(xml, "Name", ui->lineEditName);
  XmlHelper::writeXml(xml, "BaseClass", ui->lineEditBaseClass);
  XmlHelper::writeXml(xml, "ConstructorDeclaration", ui->constructor);
  XmlHelper::writeXml(xml, "DestructorDeclaration", ui->destructor);
  XmlHelper::writeXml(xml, "CopyConstructorDeclaration", ui->copyConstructor);
  XmlHelper::writeXml(xml, "CopyOperatorDeclaration", ui->copyOperator);
  XmlHelper::writeXml(xml, "MoveConstructorDeclaration", ui->moveConstructor);
  XmlHelper::writeXml(xml, "MoveOperatorDeclaration", ui->moveOperator);
  XmlHelper::writeXml(xml, "SingletonType", ui->singleton);
  XmlHelper::writeXml(xml, "DPointerType", ui->dPointer);
  XmlHelper::writeXml(xml, "QObjectMacro", ui->checkBoxQObjectMacro);
  XmlHelper::writeXml(xml, "VirtualDestructor", ui->checkBoxVirtualDesctructor);
  XmlHelper::writeXml(xml, "ExplicitConstructor", ui->checkBoxExplicitConstructor);
  XmlHelper::writeXml(xml, "Namespaces", ui->plainTextEditNamespaces);
  XmlHelper::writeXml(xml, "Interfaces", &m_interfaces);
}

QList<QPair<QString, QString> > GeneratorClass::generatedCode()
{
  QString className = ui->lineEditName->text();

  Class c(className);
  c.setConstructorDeclarationType(ui->constructor->declarationType());
  c.setDestructorDeclarationType(ui->destructor->declarationType());
  c.setCopyConstructorDeclarationType(ui->copyConstructor->declarationType());
  c.setCopyOperatorDeclarationType(ui->copyOperator->declarationType());
  c.setMoveConstructorDeclarationType(ui->moveConstructor->declarationType());
  c.setMoveOperatorDeclarationType(ui->moveOperator->declarationType());
  c.setSingletonType(ui->singleton->singletonType());
  c.setDPointerType(ui->dPointer->dPointerType());
  c.setIncludeQObjectMacro(ui->checkBoxQObjectMacro->isChecked());
  c.setDeclareConstructorExplicit(ui->checkBoxExplicitConstructor->isChecked());
  c.setDeclareDestructorVirtual(ui->checkBoxVirtualDesctructor->isChecked());

  QString baseClass = ui->lineEditBaseClass->text();
  if (!baseClass.isEmpty())
  {
    Class baseClass(ui->lineEditBaseClass->text());
    c.setBaseClass(&baseClass);
  }

  QString namespaces = ui->plainTextEditNamespaces->toPlainText();

  if (!namespaces.isEmpty())
  {
    c.setNamespaceNames(ui->plainTextEditNamespaces->toPlainText().split("\n"));
  }

  c.setInterfaces(m_interfaces);

  QList<QPair<QString, QString> > code;
  code.append(qMakePair(className + ".h", c.declaration()));
  code.append(qMakePair(className + ".cpp", c.implementation()));
  return code;
}

void GeneratorClass::on_singleton_singletonTypeChanged(int singletonType)
{
  bool enabled = true;

  if (singletonType != Class::SingletonType::NoSingleton)
  {
    ui->constructor->setDeclarationType(Class::DeclarationType::Private);
    ui->destructor->setDeclarationType(Class::DeclarationType::Private);
    ui->copyConstructor->setDeclarationType(Class::DeclarationType::Private);
    ui->copyOperator->setDeclarationType(Class::DeclarationType::Private);
    ui->moveConstructor->setDeclarationType(Class::DeclarationType::NoDeclaration);
    ui->moveOperator->setDeclarationType(Class::DeclarationType::NoDeclaration);

    enabled = false;
  }

  ui->constructor->setEnabled(enabled);
  ui->destructor->setEnabled(enabled);
  ui->copyConstructor->setEnabled(enabled);
  ui->copyOperator->setEnabled(enabled);
  ui->moveConstructor->setEnabled(enabled);
  ui->moveOperator->setEnabled(enabled);
}

void GeneratorClass::on_dPointer_dPointerTypeChanged(int dPointerType)
{
  if (dPointerType != Class::DPointerType::NoDPointer)
  {
    if (ui->copyConstructor->declarationType() == Class::DeclarationType::NoDeclaration)
    {
      ui->copyConstructor->setDeclarationType(Class::DeclarationType::Public);
    }

    if (ui->copyOperator->declarationType() == Class::DeclarationType::NoDeclaration)
    {
      ui->copyOperator->setDeclarationType(Class::DeclarationType::Public);
    }
  }
}

void GeneratorClass::addInterface()
{
  InterfaceGui* interfaceGui = new InterfaceGui();
  dynamic_cast<WidgetListEditor*>(QObject::sender())->addItem(interfaceGui);
}

void GeneratorClass::on_pushButtonInterfaces_clicked()
{
  if (m_widgetListEditor == NULL)
  {
    m_widgetListEditor = new WidgetListEditor(this);
    m_widgetListEditor->setButtonText(tr("add interface"));
    m_widgetListEditor->setWindowTitle(tr("interface editor"));
    connect(m_widgetListEditor, SIGNAL(addClicked()), this, SLOT(addInterface()));
    fillInterfaceList();
  }

  if (m_widgetListEditor->exec() == QDialog::Accepted)
  {
    m_interfaces.clear();

    QList<QWidget*> items = m_widgetListEditor->items();

    for (auto it = items.begin(); it != items.end(); it++)
    {
      InterfaceGui* interfaceGui = dynamic_cast<InterfaceGui*>(*it);
      if (interfaceGui)
      {
        m_interfaces.append(interfaceGui->interface());
      }
    }

    emit optionsChanged();
  }
  else
  {
    m_widgetListEditor->clear();
    fillInterfaceList();
  }
}

void GeneratorClass::fillInterfaceList()
{
  for (auto it = m_interfaces.begin(); it != m_interfaces.end(); it++)
  {
    InterfaceGui* interfaceGui = new InterfaceGui();
    interfaceGui->setInterface(*it);
    m_widgetListEditor->addItem(interfaceGui);
  }
}
