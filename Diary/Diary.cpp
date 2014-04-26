#include "Diary.h"
#include "ui_Diary.h"

Diary::Diary(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::Diary)
{
  ui->setupUi(this);
}

Diary::~Diary()
{
  delete ui;
}

void Diary::on_pushButtonToday_clicked()
{

}

void Diary::on_pushButtonOneDayBack_clicked()
{

}

void Diary::on_pushButtonOneDayForward_clicked()
{

}

void Diary::on_pushButtonOneMonthBack_clicked()
{

}

void Diary::on_pushButtonOneMonthForward_clicked()
{

}

void Diary::on_pushButtonOneYearBack_clicked()
{

}

void Diary::on_pushButtonOneYearForward_clicked()
{

}
