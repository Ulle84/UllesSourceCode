#include "TimeCalculator.h"
#include "ui_TimeCalculator.h"

TimeCalculator::TimeCalculator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeCalculator)
{
    ui->setupUi(this);
}

TimeCalculator::~TimeCalculator()
{
    delete ui;
}

void TimeCalculator::on_lineEditNanoseconds_editingFinished()
{
    changeTime(ui->lineEditNanoseconds->text().toDouble());
}

void TimeCalculator::on_lineEditMiroseconds_editingFinished()
{
    changeTime(ui->lineEditMiroseconds->text().toDouble() * 1000);
}

void TimeCalculator::on_lineEditMilliseconds_editingFinished()
{
    changeTime(ui->lineEditMilliseconds->text().toDouble() * 1000 * 1000);
}

void TimeCalculator::on_lineEditSeconds_editingFinished()
{
    changeTime(ui->lineEditSeconds->text().toDouble() * 1000 * 1000 * 1000);
}

void TimeCalculator::on_lineEditMinutes_editingFinished()
{
    changeTime(ui->lineEditMinutes->text().toDouble() * 1000 * 1000 * 1000 * 60);
}

void TimeCalculator::on_lineEditHours_editingFinished()
{
    changeTime(ui->lineEditHours->text().toDouble() * 1000 * 1000 * 1000 * 60 * 60);
}

void TimeCalculator::on_lineEditDays_editingFinished()
{
    changeTime(ui->lineEditDays->text().toDouble() * 1000 * 1000 * 1000 * 60 * 60 * 24);
}

void TimeCalculator::on_lineEditYears_editingFinished()
{
   changeTime(ui->lineEditYears->text().toDouble() * 1000 * 1000 * 1000 * 60 * 60 * 24 * 365);
}

void TimeCalculator::changeTime(double newTimeInNanoseconds)
{
    timeInNanoseconds = newTimeInNanoseconds;
    ui->lineEditNanoseconds->setText(QVariant(timeInNanoseconds).toString());
    ui->lineEditMiroseconds->setText(QVariant(timeInNanoseconds / 1000).toString());
    ui->lineEditMilliseconds->setText(QVariant(timeInNanoseconds / 1000 / 1000).toString());
    ui->lineEditSeconds->setText(QVariant(timeInNanoseconds / 1000 / 1000 / 1000).toString());
    ui->lineEditMinutes->setText(QVariant(timeInNanoseconds / 1000 / 1000 / 1000 / 60).toString());
    ui->lineEditHours->setText(QVariant(timeInNanoseconds / 1000 / 1000 / 1000 / 60 / 60).toString());
    ui->lineEditDays->setText(QVariant(timeInNanoseconds / 1000 / 1000 / 1000 / 60 / 60 / 24).toString());
    ui->lineEditYears->setText(QVariant(timeInNanoseconds / 1000 / 1000 / 1000 / 60 / 60 / 24 / 365).toString());
}
