#include <QDebug>

#include "InterfaceGui.h"
#include "ui_InterfaceGui.h"
#include "WidgetListEditor.h"
#include "Method.h"
#include "MethodGui.h"
#include "Interface.h"

InterfaceGui::InterfaceGui(QWidget *parent) :
  QDialog(parent),
  m_widgetListEditor(NULL),
  ui(new Ui::InterfaceGui)
{
  ui->setupUi(this);
}

InterfaceGui::~InterfaceGui()
{
  delete ui;
}

void InterfaceGui::setInterface(const Interface &interface)
{
  m_interface = interface;

  ui->lineEditName->setText(m_interface.m_name);
  ui->checkBox->setChecked(m_interface.m_toImplement);
}

Interface InterfaceGui::interface()
{
  return m_interface;
}

void InterfaceGui::setToImplementAvailable(bool available)
{
  ui->checkBox->setVisible(available);
}

void InterfaceGui::on_pushButtonMethods_clicked()
{
  if (!m_widgetListEditor)
  {
    m_widgetListEditor = new WidgetListEditor(this);
    m_widgetListEditor->setButtonText(tr("add method"));
    m_widgetListEditor->setWindowTitle(tr("method editor"));
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
  }
  else
  {
    m_widgetListEditor->clear();
    fillMethodList();
  }
}

void InterfaceGui::addMethod()
{
  MethodGui* methodGui = new MethodGui();
  methodGui->setTypeVisible(false);
  methodGui->setDeclarationTypeVisible(false);
  m_widgetListEditor->addItem(methodGui);
}

void InterfaceGui::on_lineEditName_textEdited(const QString &name)
{
  m_interface.m_name = name;
}

void InterfaceGui::on_checkBox_clicked(bool checked)
{
  m_interface.m_toImplement = checked;
}

void InterfaceGui::fillMethodList()
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
