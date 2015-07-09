#include <QClipboard>
#include <QMessageBox>
#include <QSettings>
#include <QTextCharFormat>
#include <QDateTime>

#include "DateTimeHelper.h"
#include "ui_DateTimeHelper.h"
#include "TimeCalculator.h"
#include "DateTimeAdder.h"

DateTimeHelper::DateTimeHelper(QWidget* parent) :
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

  TimeCalculator* timeCalculator = new TimeCalculator(this);
  ui->groupBoxTimeCalculator->layout()->addWidget(timeCalculator);

  DateTimeAdder* dateTimeAdder = new DateTimeAdder(this);
  ui->groupBoxDateTimeAdder->layout()->addWidget(dateTimeAdder);
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
}

void DateTimeHelper::copyDateToClipboard()
{
  QApplication::clipboard()->setText(ui->calendarWidget->selectedDate().toString(m_outputFormat));
}

void DateTimeHelper::on_lineEditUnixTime_returnPressed()
{
  bool conversionOkay;
  int time = ui->lineEditUnixTime->text().toInt(&conversionOkay, 10);

  if (conversionOkay)
  {
    ui->lineEditRealTime->setText(QDateTime::fromTime_t(time).toString("yyyy-MM-dd hh:mm:ss"));
  }
  else
  {
    QMessageBox::information(this, tr("wrong input"), tr("the input could not be interpreted"));
  }
}

void DateTimeHelper::on_lineEditRealTime_returnPressed()
{
  QDateTime dateTime = QDateTime::fromString(ui->lineEditRealTime->text(), "yyyy-MM-dd hh:mm:ss");

  if (dateTime.isValid())
  {
    ui->lineEditUnixTime->setText(QString::number(dateTime.toTime_t()));
  }
  else
  {
    QMessageBox::information(this, tr("wrong input"), tr("the input could not be interpreted"));
  }
}
