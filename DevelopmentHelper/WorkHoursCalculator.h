#ifndef WORKHOURSCALCULATOR_H
#define WORKHOURSCALCULATOR_H

#include <QWidget>

namespace Ui
{
class WorkHoursCalculator;
}

class WorkHoursCalculator : public QWidget
{
  Q_OBJECT

public:
  explicit WorkHoursCalculator(QWidget* parent = 0);
  ~WorkHoursCalculator();

private slots:
  void on_pushButtonCalculateEndOfDay_clicked();

private:
  int timeStringToMinutes(const QString& timeString);
  QString minutesToTimeString(int minutes);

  Ui::WorkHoursCalculator* ui;
};

#endif // WORKHOURSCALCULATOR_H
