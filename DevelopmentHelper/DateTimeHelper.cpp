#include <QClipboard>
#include <QMessageBox>
#include <QSettings>
#include <QTextCharFormat>

#include "DateTimeHelper.h"
#include "ui_DateTimeHelper.h"

DateTimeHelper::DateTimeHelper(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::DateTimeHelper),
  m_outputFormatDefault("ddd, dd.MM.yyyy")
{
  ui->setupUi(this);

  m_settings = new QSettings("Ulle", "DevelopmentHelper.DateTimeHelper", this);

  if (m_settings->contains("outputFormat"))
  {
    m_outputFormat = m_settings->value("outputFormat").toString();
  }
  else
  {
    m_outputFormat = m_outputFormatDefault;
  }

  ui->lineEditOutputFormat->setText(m_outputFormat);

  // select and mark today's date
  const QDate today = QDate::currentDate();
  ui->calendarWidget->setSelectedDate(today);
  QTextCharFormat todayFormat;
  todayFormat.setForeground(Qt::magenta);
  ui->calendarWidget->setDateTextFormat(today, todayFormat);
}

DateTimeHelper::~DateTimeHelper()
{
  m_settings->setValue("outputFormat", ui->lineEditOutputFormat->text());
  delete ui;
}

void DateTimeHelper::on_calendarWidget_clicked(const QDate& date)
{
  copyDateToClipboard();
}

void DateTimeHelper::on_pushButtonToday_clicked()
{
  ui->calendarWidget->setSelectedDate(QDate::currentDate());
  copyDateToClipboard();
}

void DateTimeHelper::on_pushButtonDefault_clicked()
{
  m_outputFormat = m_outputFormatDefault;
  ui->lineEditOutputFormat->setText(m_outputFormat);
}

void DateTimeHelper::on_lineEditOutputFormat_textChanged(const QString& newOutputFormat)
{
  m_outputFormat = newOutputFormat;
  copyDateToClipboard();
}

void DateTimeHelper::copyDateToClipboard()
{
  QApplication::clipboard()->setText(ui->calendarWidget->selectedDate().toString(m_outputFormat));
}
