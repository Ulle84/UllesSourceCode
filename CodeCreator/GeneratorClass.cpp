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

GeneratorClass::GeneratorClass(CodeGenerator* codeGenerator, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorClass),
  m_codeGenerator(codeGenerator),
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
}

GeneratorClass::~GeneratorClass()
{
  delete ui;
}

bool GeneratorClass::generate(const QString &folder)
{
  QString className = ui->lineEditName->text();

  if (className.isEmpty())
  {
    QMessageBox mb;
    mb.setText(tr("Please enter a name!"));
    mb.exec();
    return false;
  }

  Class c(className);
  c.setConstructorDeclarationType(ui->constructor->declarationType());
  c.setDestructorDeclarationType(ui->destructor->declarationType());
  c.setCopyConstructorDeclarationType(ui->copyConstructor->declarationType());
  c.setCopyOperatorDeclarationType(ui->copyOperator->declarationType());
  c.setMoveConstructorDeclarationType(ui->moveConstructor->declarationType());
  c.setMoveOperatorDeclarationType(ui->moveOperator->declarationType());
  c.setSingletonType(ui->singleton->singletonType());
  c.setDPointerType(ui->dPointer->dPointerType());
  c.setOutputDirectory(folder);
  c.setIncludeQObjectMacro(ui->checkBoxQObjectMacro->isChecked());
  c.setDeclareConstructorExplicit(ui->checkBoxExplicitConstructor->isChecked());
  c.setDeclareDestructorVirtual(ui->checkBoxVirtualDesctructor->isChecked());
  c.setOverwriteExistingFiles(true);

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

  /*QList<Interface> interfaces;
  QString interfaceText = ui->plainTextEditInterfaces->toPlainText();

  if (!interfaceText.isEmpty())
  {
    QStringList interfaceList = interfaceText.split("\n");
    for (auto it = interfaceList.begin(); it != interfaceList.end(); it++)
    {
      interfaces.append(Interface(*it, "void toDo();"));
    }
  }*/

  c.setInterfaces(m_interfaces);



  qDebug() << c.createHeader();
  qDebug() << "-----------------------------------------";
  qDebug() << c.createImplementation();

  ui->plainTextEditTestOutput->clear();
  ui->plainTextEditTestOutput->appendPlainText(c.createHeader());
  ui->plainTextEditTestOutput->appendPlainText("\n\n\n");
  ui->plainTextEditTestOutput->appendPlainText(c.createImplementation());

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
    /*else if (xml.name() == "Interfaces")
    {
      XmlHelper::readXml(xml, ui->plainTextEditInterfaces);
    }*/
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
  //XmlHelper::writeXml(xml, "Interfaces", ui->plainTextEditInterfaces);
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
