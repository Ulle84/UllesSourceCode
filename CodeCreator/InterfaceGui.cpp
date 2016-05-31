#include "InterfaceGui.h"
#include "ui_InterfaceGui.h"
#include "WidgetListEditor.h"
#include "Method.h"
#include "MethodGui.h"
#include "Interface.h"

InterfaceGui::InterfaceGui(Interface* interface, QWidget *parent) :
  QDialog(parent),
  m_interface(interface),
  ui(new Ui::InterfaceGui)
{
  ui->setupUi(this);

  m_widgetListEditor = new WidgetListEditor(this);
  connect(m_widgetListEditor, SIGNAL(pushButtonAddClicked()), this, SLOT(addMethod()));
}

InterfaceGui::~InterfaceGui()
{
  delete ui;
}

void InterfaceGui::on_pushButtonMethods_clicked()
{
  m_widgetListEditor->exec();
}

void InterfaceGui::addMethod()
{
  Method* method = new Method("");
  MethodGui* methodGui = new MethodGui(method);
  m_widgetListEditor->addItem(methodGui);
}

void InterfaceGui::on_lineEditName_textEdited(const QString &name)
{
  m_interface->m_name = name;
}
