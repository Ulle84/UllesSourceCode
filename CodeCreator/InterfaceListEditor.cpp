#include <QDebug>

#include "WidgetListEditor.h"
#include "InterfaceListEditor.h"
#include "ui_InterfaceListEditor.h"
#include "InterfaceGui.h"

InterfaceListEditor::InterfaceListEditor(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::InterfaceListEditor),
  m_widgetListEditor(NULL),
  m_toImplementAvailable(true)
{
  ui->setupUi(this);
}

InterfaceListEditor::~InterfaceListEditor()
{
  delete ui;
}

QList<Interface> InterfaceListEditor::interfaceList() const
{
  return m_interfaceList;
}

void InterfaceListEditor::setInterfaceList(const QList<Interface> &interfaceList)
{
  m_interfaceList = interfaceList;
}

void InterfaceListEditor::setText(const QString &text)
{
  ui->pushButtonInterfaceList->setText(text);
}

void InterfaceListEditor::setToImplementAvailable(bool available)
{
  if (m_widgetListEditor != NULL)
  {
    QList<QWidget*> items = m_widgetListEditor->items();

    for (auto it = items.begin(); it != items.end(); it++)
    {
      InterfaceGui* interfaceGui = dynamic_cast<InterfaceGui*>(*it);
      if (interfaceGui)
      {
        interfaceGui->setToImplementAvailable(available);
      }
    }
  }

  m_toImplementAvailable = available;
}

void InterfaceListEditor::on_pushButtonInterfaceList_clicked()
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
    m_interfaceList.clear();

    QList<QWidget*> items = m_widgetListEditor->items();

    for (auto it = items.begin(); it != items.end(); it++)
    {
      InterfaceGui* interfaceGui = dynamic_cast<InterfaceGui*>(*it);
      if (interfaceGui)
      {
        m_interfaceList.append(interfaceGui->interface());
      }
    }

    emit interfaceListChanged();
  }
  else
  {
    m_widgetListEditor->clear();
    fillInterfaceList();
  }
}

void InterfaceListEditor::addInterface()
{
  InterfaceGui* interfaceGui = new InterfaceGui();
  interfaceGui->setToImplementAvailable(m_toImplementAvailable);
  dynamic_cast<WidgetListEditor*>(QObject::sender())->addItem(interfaceGui);
}

void InterfaceListEditor::fillInterfaceList()
{
  for (auto it = m_interfaceList.begin(); it != m_interfaceList.end(); it++)
  {
    InterfaceGui* interfaceGui = new InterfaceGui();
    interfaceGui->setInterface(*it);
    interfaceGui->setToImplementAvailable(m_toImplementAvailable);
    m_widgetListEditor->addItem(interfaceGui);
  }
}
