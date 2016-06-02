#include <QDebug>

#include "Method.h"
#include "MethodGui.h"
#include "ui_MethodGui.h"
#include "WidgetListEditor.h"
#include "ParameterGui.h"

MethodGui::MethodGui(QWidget *parent) :
  QWidget(parent),
  m_widgetListEditor(NULL),
  ui(new Ui::MethodGui)
{
  ui->setupUi(this);

  ui->comboBoxDeclarationType->addItem(tr("public"), Method::DeclarationType::Public);
  ui->comboBoxDeclarationType->addItem(tr("protected"), Method::DeclarationType::Protected);
  ui->comboBoxDeclarationType->addItem(tr("private"), Method::DeclarationType::Private);

  ui->comboBoxType->addItem(tr("normal"), Method::Type::Normal);
  ui->comboBoxType->addItem(tr("virtual"), Method::Type::Virtual);
  ui->comboBoxType->addItem(tr("pure virtual"), Method::Type::PureVirtual);
}

MethodGui::~MethodGui()
{
  delete ui;
}

void MethodGui::setMethod(const Method &method)
{
  m_method = method;

  ui->lineEditName->setText(m_method.m_name);
  ui->lineEditReturnType->setText(m_method.m_returnType);
  // TODO set state of combo boxes
}

Method MethodGui::method()
{
  return m_method;
}

void MethodGui::on_comboBoxDeclarationType_currentIndexChanged(const QString &arg1)
{
  m_method.m_declarationType = static_cast<Method::DeclarationType>(ui->comboBoxDeclarationType->itemData(ui->comboBoxDeclarationType->currentIndex()).toInt());
}

void MethodGui::on_comboBoxType_currentIndexChanged(const QString &arg1)
{
  m_method.m_type = static_cast<Method::Type>(ui->comboBoxType->itemData(ui->comboBoxType->currentIndex()).toInt());
}

void MethodGui::on_lineEditReturnType_textEdited(const QString &returnType)
{
  m_method.m_returnType = returnType;
}

void MethodGui::on_lineEditName_textEdited(const QString &name)
{
  m_method.m_name = name;
}

void MethodGui::on_pushButtonParameters_clicked()
{
  if (!m_widgetListEditor)
  {
    m_widgetListEditor = new WidgetListEditor(this);
    connect(m_widgetListEditor, SIGNAL(addClicked()), this, SLOT(addParameter()));
    fillParameterList();
  }

  if (m_widgetListEditor->exec() == QDialog::Accepted)
  {
    m_method.clear();

    QList<QWidget*> items = m_widgetListEditor->items();

    for (auto it = items.begin(); it != items.end(); it++)
    {
      ParameterGui* parameterGui = dynamic_cast<ParameterGui*>(*it);
      if (parameterGui)
      {
        m_method.append(parameterGui->parameter());
      }
    }
  }
  else
  {
    m_widgetListEditor->clear();
    fillParameterList();
  }
}

void MethodGui::addParameter()
{
  ParameterGui* parameterGui = new ParameterGui();
  m_widgetListEditor->addItem(parameterGui);
}

void MethodGui::fillParameterList()
{
  for (auto it = m_method.begin(); it != m_method.end(); it++)
  {
    ParameterGui* parameterGui = new ParameterGui();
    parameterGui->setParameter(*it);
    m_widgetListEditor->addItem(parameterGui);
  }
}
