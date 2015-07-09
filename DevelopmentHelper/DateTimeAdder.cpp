#include "DateTimeAdder.h"
#include "ui_DateTimeAdder.h"

DateTimeAdder::DateTimeAdder(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::DateTimeAdder),
  m_seconds(0)
{
  ui->setupUi(this);
}

DateTimeAdder::~DateTimeAdder()
{
  delete ui;
}

void DateTimeAdder::on_spinBox_valueChanged(int seconds)
{
  m_seconds = seconds;
  calculate();
}

void DateTimeAdder::on_dateTimeEdit_dateTimeChanged(const QDateTime& dateTime)
{
  m_dateTime = dateTime;
  calculate();
}

void DateTimeAdder::calculate()
{
  QDateTime dateTime = m_dateTime.addSecs(m_seconds);
  ui->label_3->setText(dateTime.toString("dd.MM.yy hh:mm:ss"));
}