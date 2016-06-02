#include "InterfaceGui.h"
#include "ui_InterfaceGui.h"
#include "WidgetListEditor.h"
#include "Method.h"
#include "MethodGui.h"
#include "Interface.h"

InterfaceGui::InterfaceGui(QWidget *parent) :
  QDialog(parent),
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

void InterfaceGui::setInterface(const Interface &interface)
{
  m_interface = interface;

  ui->lineEditName->setText(m_interface.m_name);
  ui->checkBox->setChecked(m_interface.m_implementInterface);
}

Interface InterfaceGui::interface()
{
  return m_interface;
}

void InterfaceGui::on_pushButtonMethods_clicked()
{
  m_widgetListEditor->exec();
}

void InterfaceGui::addMethod()
{
  MethodGui* methodGui = new MethodGui();
  m_widgetListEditor->addItem(methodGui);
}

void InterfaceGui::on_lineEditName_textEdited(const QString &name)
{
  m_interface.m_name = name;
}

void InterfaceGui::on_checkBox_clicked(bool checked)
{
  m_interface.m_implementInterface = checked;
}
