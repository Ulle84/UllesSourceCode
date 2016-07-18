#include "ui_InterfaceEditor.h"

#include "InterfaceEditor.h"
#include "MethodGui.h"
#include "WidgetListEditor.h"

InterfaceEditor::InterfaceEditor(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::InterfaceEditor),
  m_widgetListEditor(NULL)
{
  ui->setupUi(this);
}

InterfaceEditor::~InterfaceEditor()
{
  delete ui;
}

Interface InterfaceEditor::interface() const
{
  return m_interface;
}

void InterfaceEditor::setInterface(const Interface& interface)
{
  m_interface = interface;
}

void InterfaceEditor::setText(const QString& text)
{
  ui->pushButtonInterface->setText(text);
}

void InterfaceEditor::on_pushButtonInterface_clicked()
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

    emit interfaceChanged();
  }
  else
  {
    m_widgetListEditor->clear();
    fillMethodList();
  }
}

void InterfaceEditor::addMethod()
{
  MethodGui* methodGui = new MethodGui();
  methodGui->setTypeVisible(false);
  methodGui->setDeclarationTypeVisible(false);
  dynamic_cast<WidgetListEditor*>(QObject::sender())->addItem(methodGui);
}

void InterfaceEditor::fillMethodList()
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
