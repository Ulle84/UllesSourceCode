#include "WorkHoursCalculator.h"
#include "ui_WorkHoursCalculator.h"

WorkHoursCalculator::WorkHoursCalculator(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::WorkHoursCalculator)
{
  ui->setupUi(this);
}

WorkHoursCalculator::~WorkHoursCalculator()
{
  delete ui;
}

void WorkHoursCalculator::on_pushButtonCalculateEndOfDay_clicked()
{
  int startOfDay = timeStringToMinutes(ui->lineEditStartOfDay->text());
  int startOfBreak = timeStringToMinutes(ui->lineEditStartOfBreak->text());
  int endOfBreak = timeStringToMinutes(ui->lineEditEndOfBreak->text());
  int workingTime = timeStringToMinutes(ui->lineEditWorkingTime->text());

  int breakDuration = endOfBreak - startOfBreak;

  if (breakDuration < 0)
  {
    ui->labelEndOfDay->setText("error");
  }

  int endOfDay = startOfDay + breakDuration + workingTime;

  ui->labelEndOfDay->setText(minutesToTimeString(endOfDay));
}

int WorkHoursCalculator::timeStringToMinutes(const QString &timeString)
{
  QStringList seperated = timeString.split(':');

  if (seperated.length() != 2)
  {
    return 0;
  }

  return seperated.at(0).toInt() * 60 + seperated.at(1).toInt();
}

QString WorkHoursCalculator::minutesToTimeString(int minutes)
{
  return QString("%1:%2").arg(minutes / 60).arg(minutes % 60);
}
