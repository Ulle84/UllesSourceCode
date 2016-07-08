#include <QDebug>
#include <QMessageBox>

#include "GeneratorInterface.h"
#include "ui_GeneratorInterface.h"
#include "Options.h"
#include "CodeGenerator.h"
#include "XmlHelper.h"
#include "InterfaceHelper.h"
#include "Class.h"
#include "Interface.h"
#include "Method.h"
#include "WidgetListEditor.h"
#include "MethodGui.h"

GeneratorInterface::GeneratorInterface(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::GeneratorInterface),
  m_widgetListEditor(NULL)
{
  ui->setupUi(this);

  connect(ui->lineEditName, SIGNAL(textEdited(QString)), this, SIGNAL(optionsChanged()));
  connect(ui->checkBoxPostfix, SIGNAL(stateChanged(int)), this, SIGNAL(optionsChanged()));
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
      XmlHelper::readXml(xml, &m_interface);
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
  XmlHelper::writeXml(xml, &m_interface);
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
  c.setConstructorDeclarationType(Class::DeclarationType::NoDeclaration);
  c.setDeclareDestructorVirtual(true);

  m_interface.setAllMethodsPublicPureVirtual();
  c.setInterface(m_interface);

  QList<QPair<QString, QString> > code;
  code.append(qMakePair(interfaceName + ".h", c.declaration()));
  return code;
}

void GeneratorInterface::on_pushButtonDefineMethods_clicked()
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

void GeneratorInterface::addMethod()
{
  MethodGui* methodGui = new MethodGui();
  methodGui->setTypeVisible(false);
  methodGui->setDeclarationTypeVisible(false);
  dynamic_cast<WidgetListEditor*>(QObject::sender())->addItem(methodGui);
}

void GeneratorInterface::fillMethodList()
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
