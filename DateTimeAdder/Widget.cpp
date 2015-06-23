#include "Widget.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget),
  m_seconds(0)
{
  ui->setupUi(this);
  m_dateTime = ui->dateTimeEdit->dateTime();
  calculate();
}

Widget::~Widget()
{
  delete ui;
}

void Widget::on_spinBox_valueChanged(int seconds)
{
  m_seconds = seconds;
  calculate();
}

void Widget::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
  m_dateTime = dateTime;
  calculate();
}

void Widget::calculate()
{
  QDateTime dateTime = m_dateTime.addSecs(m_seconds);
  ui->label_3->setText(dateTime.toString("dd.MM.yy hh:mm:ss"));
}
