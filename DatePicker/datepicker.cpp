#include "datepicker.h"
#include "ui_datepicker.h"
#include <QClipboard>
#include <QTextCharFormat>
#include <QMessageBox>

DatePicker::DatePicker(QWidget* parent) :
  QWidget(parent),
  ui(new Ui::DatePicker)
{
  ui->setupUi(this);

  // set output format
  outputFormatDefault = "ddd, dd.MM.yyyy"; // ToDo - make this const!
  outputFormat = outputFormatDefault;
  ui->lineEdit->setText(outputFormat);

  // select and mark today's date
  const QDate today = QDate::currentDate();
  ui->calendarWidget->setSelectedDate(today);
  QTextCharFormat todayFormat;
  todayFormat.setForeground(Qt::magenta);
  ui->calendarWidget->setDateTextFormat(today, todayFormat);
}

DatePicker::~DatePicker()
{
  delete ui;
}

void DatePicker::on_calendarWidget_clicked(const QDate& date)
{
  QApplication::clipboard()->setText(date.toString(outputFormat));
}

void DatePicker::on_pushButton_clicked()
{
  ui->calendarWidget->setSelectedDate(QDate::currentDate());
}

void DatePicker::on_pushButton_2_clicked()
{
  // ToDo - create and load as resource
  QMessageBox::about(this, "About DatePicker", "With DatePicker you can select a date. \nThis date will be copied into the clipboard.\n\nOutput format syntax:\n d	the day as number without a leading zero (1 to 31)\ndd	the day as number with a leading zero (01 to 31)\nddd	the abbreviated localized day name (e.g. 'Mon' to 'Sun').\ndddd	the long localized day name (e.g. 'Monday' to 'Sunday').\nM	the month as number without a leading zero (1 to 12)\nMM	the month as number with a leading zero (01 to 12)\nMMM	the abbreviated localized month name (e.g. 'Jan' to 'Dec').\nMMMM	the long localized month name (e.g. 'January' to 'December').\nyy	the year as two digit number (00 to 99)\nyyyy	the year as four digit number.");
}

void DatePicker::on_lineEdit_textChanged(const QString& newOutputFormat)
{
  outputFormat = newOutputFormat;
}

void DatePicker::on_pushButton_3_clicked()
{
  outputFormat = outputFormatDefault;
  ui->lineEdit->setText(outputFormat);
}
