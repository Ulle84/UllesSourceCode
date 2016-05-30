#include "ParameterGui.h"
#include "ui_ParameterGui.h"

ParameterGui::ParameterGui(Parameter* parameter, QWidget *parent) :
  QWidget(parent),
  m_parameter(parameter),
  ui(new Ui::ParameterGui)
{
  ui->setupUi(this);
  ui->lineEditDefaultValue  ->setText(m_parameter->m_defaultValue);
  ui->lineEditName->setText(m_parameter->m_name);
  ui->lineEditType->setText(m_parameter->m_type);
}

ParameterGui::~ParameterGui()
{
  delete ui;
}

void ParameterGui::on_lineEditType_textEdited(const QString &type)
{
  m_parameter->m_type = type;
}

void ParameterGui::on_lineEditName_textEdited(const QString &name)
{
  m_parameter->m_name = name;
}

void ParameterGui::on_lineEditDefaultValue_textEdited(const QString &defaultValue)
{
  m_parameter->m_defaultValue = defaultValue;
}
