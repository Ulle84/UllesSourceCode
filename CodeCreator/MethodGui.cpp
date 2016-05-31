#include <QDebug>

#include "Method.h"
#include "MethodGui.h"
#include "ui_MethodGui.h"
#include "WidgetListEditor.h"
#include "ParameterGui.h"

MethodGui::MethodGui(Method* method, QWidget *parent) :
  QWidget(parent),
  m_method(method),
  ui(new Ui::MethodGui)
{
  ui->setupUi(this);

  ui->comboBoxDeclarationType->addItem(tr("public"), Method::DeclarationType::Public);
  ui->comboBoxDeclarationType->addItem(tr("protected"), Method::DeclarationType::Protected);
  ui->comboBoxDeclarationType->addItem(tr("private"), Method::DeclarationType::Private);

  ui->comboBoxType->addItem(tr("normal"), Method::Type::Normal);
  ui->comboBoxType->addItem(tr("virtual"), Method::Type::Virtual);
  ui->comboBoxType->addItem(tr("pure virtual"), Method::Type::PureVirtual);

  m_widgetListEditor = new WidgetListEditor(this);
  connect(m_widgetListEditor, SIGNAL(pushButtonAddClicked()), this, SLOT(addParameter()));
}

MethodGui::~MethodGui()
{
  delete ui;
}

void MethodGui::on_comboBoxDeclarationType_currentIndexChanged(const QString &arg1)
{
  m_method->m_declarationType = static_cast<Method::DeclarationType>(ui->comboBoxDeclarationType->itemData(ui->comboBoxDeclarationType->currentIndex()).toInt());
}

void MethodGui::on_comboBoxType_currentIndexChanged(const QString &arg1)
{
  m_method->m_type = static_cast<Method::Type>(ui->comboBoxType->itemData(ui->comboBoxType->currentIndex()).toInt());
}

void MethodGui::on_lineEditReturnType_textEdited(const QString &returnType)
{
  m_method->m_returnType = returnType;
}

void MethodGui::on_lineEditName_textEdited(const QString &name)
{
  m_method->m_name = name;
}

void MethodGui::on_pushButtonParameters_clicked()
{
  m_widgetListEditor->exec();
}

void MethodGui::addParameter()
{
  Parameter* parameter = new Parameter("");
  ParameterGui* parameterGui = new ParameterGui(parameter);
  m_widgetListEditor->addItem(parameterGui);
}
