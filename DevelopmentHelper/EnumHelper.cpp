#include <QApplication>
#include <QClipboard>

#include "EnumHelper.h"
#include "ui_EnumHelper.h"

EnumHelper::EnumHelper(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::EnumHelper)
{
  ui->setupUi(this);
}

EnumHelper::~EnumHelper()
{
  delete ui;
}

void EnumHelper::on_pushButtonCreateCodeEnum_clicked()
{
  updateValues();

  QString code = "enum ";
  code.append(ui->lineEditEnum->text());
  code.append("\n{\n");

  unsigned int counter = 0;
  for (auto it = m_values.begin(); it != m_values.end(); it++)
  {
    if (it != m_values.begin())
    {
      code.append(",\n");
    }
    code.append(QString("  %1 = %2").arg(*it).arg(counter++));
  }

  code.append("\n};");

  QApplication::clipboard()->setText(code);
}

void EnumHelper::on_pushButtonCreateCodeSwitch_clicked()
{
  updateValues();

  QString code = "switch (";
  code.append(ui->lineEditEnum->text());
  code.append(")\n{\n");

  for (auto it = m_values.begin(); it != m_values.end(); it++)
  {
    code.append(QString("case %1:\n  // TODO\n  break;\n\n").arg(*it));
  }

  code.append("default:\n  // TODO\n}");

  QApplication::clipboard()->setText(code);
}

void EnumHelper::updateValues()
{
  m_values.clear();
  m_values = ui->plainTextEditValues->toPlainText().split('\n');
}
